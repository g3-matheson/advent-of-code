#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main()
{
	string s;
	ll fresh = 0;
	vector<pair<ll,ll>> intervals;

	while(cin >> s)
	{
		if(s == "X") break;
		auto minus = s.find('-');
		intervals.push_back({stoll(s.substr(0, minus)), stoll(s.substr(minus+1))});
	}
	
	vector<bool> skip = vector<bool>(intervals.size(), false);

	for(int i = 0; i < intervals.size(); i++)
	{
		if(skip[i]) continue;

		for(int j = 0; j < intervals.size(); j++)
		{
			if(i==j || skip[j]) continue;
			auto i1 = intervals[i];
			auto i2 = intervals[j];

			ll a1 = i1.first, b1 = i1.second;
			ll a2 = i2.first, b2 = i2.second;

			if(a1 <= a2 && b2 <= b1) skip[j] = true; // i2 is inside of or equal to i1
			else if(a2 <= a1 && b1 < b2) skip[i] = true; 	 // i1 is inside of i2
			/*
				|__i__|
				  |__j__|
			*/
			else if(a1 < a2 && a2 <= b1 && b1 < b2) intervals[i].second = a2-1;
			/*
				   |__i__|
				|__j__|
			*/
			else if(a2 < a1 && b2 >= a1 && b2 < b1) intervals[i].first = b2+1;
		}
	}

	for(int i = 0; i < intervals.size(); i++)
	{
		if(skip[i]) continue;
		auto interval = intervals[i];
		fresh += (interval.second - interval.first) + 1;
	}

	cout << fresh << endl;
	return 0;
}