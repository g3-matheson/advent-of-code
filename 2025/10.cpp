#include <climits>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using namespace std;

/*
	Input: [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
	[light diagram] (button wiring schematics) {joltage requirements}
	To start a machine, its indicator lights must match the [light diagram] where . is OFF and # is ON
		Lights start as . OFF
	Pick (wiring schematics) to 'use' (by pushing buttons in them) that toggle 0-indexed lights on/off
	Return the least number of button pushes required to achieve the desired light pattern.	
*/

int pow2(int n)
{
	int result = 1;
	for(int i = 0; i < n; i++) result *= 2;
	return result;
}

string base2(int n, int l)
{
	string s = "";
	while (n > 0)
	{
		int d = n % 2;
		s = ((char)((int)'0' + d)) + s;
		n /= 2;
	}

	while(s.size() < l) s = "0" + s; // pad with 0s for toggles
	return s;
}

void pressButton(const vector<vector<int>>& buttons, int pushed, vector<bool>& lights)
{
	for(int i = 0; i < buttons[pushed].size(); i++) lights[buttons[pushed][i]] = !lights[buttons[pushed][i]];
}

void getInput(auto& lights, auto& buttons)
{
	string s;
	int count = 0;
	while(getline(cin, s))
	{
		for(auto c : s.substr(1, s.find(']')-1)) lights[count].push_back(c == '.' ? false : true);	

		auto i = s.find('(');
		while(i != string::npos)
		{
			auto j = s.find(')', i);
			string wiring = s.substr(i+1, (j-i-1));

			vector<int> button;
			for(auto c : wiring
						| views::split(',') 
						| views::transform([](auto&& x){return string(x.begin(), x.end());}))
			{
				button.push_back(stoi(c));
			}

			buttons[count].push_back(move(button));

			i = s.find('(', i+1);
		}
		count++;
	}
}

int main()
{
	int n = 171;
	vector<vector<bool>> lights = vector<vector<bool>>(n);
	vector<vector<vector<int>>> buttons = vector<vector<vector<int>>>(n);

	getInput(lights, buttons);
	
	int presses, combinations, totalPresses = 0;
	for(int i = 0; i < lights.size(); i++)
	{
		presses = INT_MAX;
		vector<bool> goal = lights[i];
		combinations = pow2(buttons[i].size()) - 1;

		for(int j = 0; j < combinations; j++)
		{
			auto toggles = base2(j, buttons[i].size()) | views::transform([](char c) { return c - '0'; });

			vector<bool> tempLights = vector<bool>(goal.size(), false);

			for(int t = 0; t < toggles.size(); t++)
			{ 
				if(toggles[t] == 1) pressButton(buttons[i], t, tempLights);
			}

			if(tempLights == goal) 
			{				
				int sum = accumulate(toggles.begin(), toggles.end(), 0);
				presses = min(presses, sum);
			}
		}

		totalPresses += presses;
	}
 
	cout << totalPresses << endl;

	return 0;
}