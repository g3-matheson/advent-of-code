#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ranges>

using namespace std;
using ll = long long;

ll dfs(unordered_map<string, vector<string>>& devices, unordered_set<string> seen, string device)
{
	if(device == "out") return 1;
	ll count = 0;

	seen.insert(device);
	
	for(auto neighbor : devices[device])
	{	
		if(!seen.contains(neighbor)) count += dfs(devices, seen, neighbor);
	}
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

	for(auto neighbor : devices["you"]) 
		count += dfs(devices, unordered_set<string>(), neighbor);

	cout << count << endl;

	return 0;
}