#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main()
{
	string s;
	int fresh = 0;
	vector<pair<ll,ll>> intervals;

	while(cin >> s)
	{
		if(s == "X") break;
		auto minus = s.find('-');
		intervals.push_back({stoll(s.substr(0, minus)), stoll(s.substr(minus+1))});
	}
	
	while(cin >> s)
	{
		auto num = stoll(s);
		if (any_of(intervals.begin(), intervals.end(), [&](auto const& i){
			return i.first <= num && i.second >= num;
		})) fresh++;
	}

	cout << fresh << endl;
	return 0;
}