#include <iostream>
#include <format>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ranges>

using namespace std;
using ll = long long;

struct State {
    string device;
    bool seen_dac;
    bool seen_fft;

    bool operator==(const State& o) const {
        return device == o.device &&
               seen_dac == o.seen_dac &&
               seen_fft == o.seen_fft;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        size_t h1 = hash<string>{}(s.device);
        size_t h2 = hash<bool>{}(s.seen_dac);
        size_t h3 = hash<bool>{}(s.seen_fft);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

/*
	Depth-First Search, with some tweeks
	- Base Case: find "out" -> return 1 if passed thru "dac" and "fft", otherwise 0
	- State is used to memoize repetitive branches:
		-> not enough to just store device because it might be reached before/after dac/fft
		-> could also use memo[{device, target}] if svr -> dac/fft -> fft/dac -> out were done separately
*/
ll dfs(const unordered_map<string, vector<string>>& devices, unordered_map<State,ll,StateHash>& memo,
		unordered_set<string>& seen, string device)
{
	if (device == "out" && seen.contains("dac") && seen.contains("fft")) return 1; 
	else if (device == "out") return 0; 

	State st {device, seen.contains("dac"), seen.contains("fft")};
	if(memo.contains(st)) return memo[st];

	seen.insert(device);

	ll count = 0;
	for(const auto& neighbor : devices.at(device))
	{	
		if(!seen.contains(neighbor)) 
		{
			unordered_set<string> seen_copy = seen; // this was very slow but with memoization seems tolerable
			count += dfs(devices, memo, seen_copy, neighbor);
		}
	}

	memo[st] = count;
	return count;
}

int main()
{
	string s;
	unordered_map<string, vector<string>> devices;
	
	while(getline(cin, s))
	{
		string from = s.substr(0, s.find(':')); 
		devices[from] = s.substr(s.find(':')+2) 
					| views::split(' ')
					| views::transform([](auto&& x){ return string(x.begin(), x.end()); })
					| ranges::to<vector>();
	} 

	ll count = 0;
	for(const auto& neighbor : devices.at("svr"))
	{
		unordered_map<State,ll,StateHash> memo;
		unordered_set<string> seen;
		count += dfs(devices, memo, seen, neighbor);
	}

	cout << count << endl;

	return 0;
}