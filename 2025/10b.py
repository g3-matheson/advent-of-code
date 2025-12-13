import pulp

'''
    Attemping this in C++ was a nightmare.
    Google's OR-Tools has an LP Solver, but I could not install it
        -> some sort of dependency problem with protobuf or something
'''

def solve_line(line):
    parts = line.split()

    buttons = []
    for p in parts:
        if p.startswith("("):
            nums = list(map(int, p[1:-1].split(",")))
            buttons.append(nums)

    targets_part = next(p for p in parts if p.startswith("{"))
    targets = list(map(int, targets_part[1:-1].split(",")))

    num_buttons = len(buttons)
    num_meters = len(targets)

    prob = pulp.LpProblem("joltage", pulp.LpMinimize)

    p = [ pulp.LpVariable(f"p_{i}", lowBound=0, cat="Integer")
        for i in range(num_buttons) ]

    prob += pulp.lpSum(p)

    for j in range(num_meters):
        prob += ( pulp.lpSum(p[i] for i in range(num_buttons) if j in buttons[i]) == targets[j] )

    status = prob.solve(pulp.PULP_CBC_CMD(msg=False))
    # should not happen, assumed that each line has at least one solution
    if status != pulp.LpStatusOptimal:
        raise RuntimeError("No Solution!")

    return sum(int(p[i].value()) for i in range(num_buttons))

def main():
    total = 0
    with open("10.txt") as f:
        for line in f:
            total += solve_line(line)

    print("Minimum total presses =", total)

if __name__ == "__main__":
    main()