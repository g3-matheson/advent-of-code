#include <iostream>
#include <vector>

#include <ranges>

using namespace std;
using ll = long long;

ll area (const vector<ll>& x, const vector<ll>& y)
{
	return abs(x[0] - y[0] + 1) * abs(x[1] - y[1] + 1);
}

int main()
{
	string s;
	vector<vector<ll>> points;

	while(cin >> s)
	{
		points.push_back(s | views::split(',') 
			| views::transform([](auto&& x){
				return stoll(string(x.begin(), x.end())); })
			| ranges::to<vector>());		
	}

	ll maxArea = 0;

	for(int i = 0; i < points.size()-1; i++)
	{
		for(int j = i+1; j < points.size(); j++)
		{
			maxArea = max(maxArea, area(points[i], points[j]));
		}
	}

	cout << maxArea << endl;

	return 0;
}