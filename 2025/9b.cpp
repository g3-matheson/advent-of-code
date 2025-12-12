#include <climits>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <ranges>

using namespace std;
using ll = long long;

/*
	1) store green lines
	2) for each fixed x, find intervals [y_i, y_j] that are in green area (same for y)
	3) for each pair of red corners, check if all 4 border sides are in green area using (2)
	4) compute area if (3) check passes
*/

ll area (const vector<ll>& x, const vector<ll>& y)
{
	return (abs(x[0] - y[0]) + 1LL) * (abs(x[1] - y[1]) + 1LL);
}

// this could maybe be optimized but it runs fast enough
bool intervalCheck(const vector<pair<ll,ll>>& intervals, ll low, ll high)
{
	for(auto& [l, r] : intervals)
	{
		if(l <= low && high <= r) return true;
	}
	return false;
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

	int n = points.size();
	unordered_map<ll, vector<pair<ll,ll>>> greensV, greensH;
	unordered_set<ll> xs, ys;
	for(int i = 0; i < n; i++)
	{			
		auto a = points[i], b = points[(i+1)%n];
		xs.insert(a[0]);
		xs.insert(b[0]);
		ys.insert(a[1]);
		ys.insert(b[1]);

		if(a[1] == b[1]) greensH[a[1]].push_back({min(a[0], b[0]), max(a[0], b[0])});
		if(a[0] == b[0]) greensV[a[0]].push_back({min(a[1], b[1]), max(a[1], b[1])});
	}
	
	// find intervals along each fixed x,y value for which they are included in the green area
	// < r/t exclusive to avoid double counting which would create intervals like (y1, y2), (y2, y3)
	unordered_map<ll, vector<pair<ll,ll>>> xIntervals, yIntervals;
	for(auto& x : xs)
	{
		vector<int> mergedY;
		for(auto& [y, intervals] : greensH)
		{
			for(auto& [l, r] : intervals)
			{
				if(l <= x && x < r) mergedY.push_back(y);
			}
		}
		sort(mergedY.begin(), mergedY.end());
		for(size_t i = 0; i+1 < mergedY.size(); i+=2) xIntervals[x].push_back({mergedY[i], mergedY[i+1]});
	}

	for(auto& y : ys)
	{
		vector<int> mergedX;
		for(auto& [x, intervals] : greensV)
		{
			for(auto& [b, t] : intervals)
			{
				if(b <= y && y < t) mergedX.push_back(x);
			}
		}
		sort(mergedX.begin(), mergedX.end());
		for(size_t i = 0; i+1 < mergedX.size(); i+=2) yIntervals[y].push_back({mergedX[i], mergedX[i+1]});
	}

	ll maxArea = 0;

	for(int i = 0; i < n-1; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			auto a = points[i], b = points[j];
			if(a[0] == b[0] || a[1] == b[1]) continue; // 0 area 

			auto minX = min(a[0], b[0]), maxX = max(a[0], b[0]);
			auto minY = min(a[1], b[1]), maxY = max(a[1], b[1]);

			if(intervalCheck(xIntervals[minX], minY, maxY) && intervalCheck(xIntervals[maxX], minY, maxY)
			&& intervalCheck(yIntervals[minY], minX, maxX) && intervalCheck(yIntervals[maxY], minX, maxX))
			{
				maxArea = max(maxArea, area(a, b));
			}
		}
	}

	cout << maxArea << endl;

	return 0;
}