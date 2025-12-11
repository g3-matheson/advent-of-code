#include <format>
#include <iostream>
#include <unordered_set>
#include <vector>

#include <ranges>

using namespace std;
using ll = long long;

struct PairHash 
{
	size_t operator()(const pair<ll,ll>& p) const noexcept
	{
		return hash<ll>()(p.first) * 31 ^ hash<ll>()(p.second);
	}
};

void fillGreens(unordered_set<pair<ll,ll>, PairHash>& greens)
{
	unordered_set<pair<ll,ll>, PairHash> newGreens;
	for(auto& g1 : greens)
	{
		for(auto& g2 : greens)
		{
			if(g1.first == g2.first)
			{
				for(int y = min(g1.second, g2.second); y <= max(g1.second, g2.second); y++)
				{
					newGreens.insert({g1.first, y});
				}
			}
			if(g1.second == g2.second)
			{
				for(int x = min(g1.first, g2.first); x <= max(g1.first, g2.first); x++)
				{
					newGreens.insert({x, g1.second});
				}
			}
		}
	}

	for(auto& g : newGreens) greens.insert(g);
}

bool greenCheck(const vector<ll>&a, const vector<ll>&b, unordered_set<pair<ll,ll>, PairHash>& greens)
{
	for(ll x = min(a[0], b[0]); x <= max(a[0], b[0]); x++) 
	{
		if(!greens.contains({x, a[1]}) || !greens.contains({x, b[1]})) return false;
	}
	for(ll y = min(a[1], b[1]); y <= max(a[1], b[1]); y++)
	{
		if(!greens.contains({a[0], y}) || !greens.contains({b[0], y})) return false;
	}
	return true; 
}

ll area (const vector<ll>& x, const vector<ll>& y)
{
	return abs(x[0] - y[0] + 1) * abs(x[1] - y[1] + 1);
}

int main()
{
	string s;
	vector<vector<ll>> points;
	unordered_set<pair<ll,ll>, PairHash>* greens = new unordered_set<pair<ll,ll>, PairHash>();

	while(cin >> s)
	{
		points.push_back(s | views::split(',') 
			| views::transform([](auto&& x){
				return stoll(string(x.begin(), x.end())); })
			| ranges::to<vector>());		
	}

	for(int i = 0; i < points.size(); i++)
	{
		vector<ll> a = points[i], b = points[(i+1) % points.size()];
		for(ll x = min(a[0], b[0]); x <= max(a[0], b[0]); x++) 
		{
			greens->insert({x, a[1]});
			greens->insert({x, b[1]});
		}
		for(ll y = min(a[1], b[1]); y <= max(a[1], b[1]); y++)
		{
			greens->insert({a[0], y});
			greens->insert({b[0], y});
		}
	}

	fillGreens(*greens);

	ll maxArea = 0;
	for(int i = 0; i < points.size()-1; i++)
	{
		for(int j = i+1; j < points.size(); j++)
		{
			if(greenCheck(points[i], points[j], *greens)) maxArea = max(maxArea, area(points[i], points[j]));
		}
	}

	cout << maxArea << endl;

	delete greens;
	return 0;
}