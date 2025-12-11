// note: requires g++14 & c++23 for ranges:to
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <algorithm>
#include <numeric>
#include <ranges>

using namespace std;
using ll = unsigned long long;

/*
	Input: (x,y,z) per line1
	Connect 1000 pairs of points with lowest Euclidean distance
	Output: product of sizes of 3 largest connected collections of points
*/

ll dist(const vector<int>& a, const vector<int>& b)
{
	return (ll)	(b[0] - a[0]) * (ll) (b[0] - a[0])
		+  (ll)	(b[1] - a[1]) * (ll) (b[1] - a[1])
		+  (ll)	(b[2] - a[2]) * (ll) (b[2] - a[2]);
}

int main()
{
	string s;
	vector<vector<int>> points;
	vector<tuple<int, int, ll>> distances;

	while(cin >> s)
	{
		points.push_back(s 	| views::split(',')
							| views::transform([](auto&& c) { return stoi(string(c.begin(), c.end())); })
							| ranges::to<vector>());
	}

	for(int i = 0; i < points.size()-1; i++)
	{
		for(int j = i+1; j < points.size(); j++)
		{
			distances.push_back({i, j, dist(points[i], points[j])});
		}
	}

	partial_sort(distances.begin(), distances.begin() + 1000, distances.end(),
		[](const auto& a, const auto& b)
		{
			return get<2>(a) < get<2>(b);
		});

	unordered_map<int, unordered_set<int>> linkedIndices;
	for(int i = 0; i < 1000; i++) linkedIndices.insert({i, {i}});

	vector<int> indexChanges = vector<int>(points.size());
	iota(indexChanges.begin(), indexChanges.end(), 0);

	for(int i = 0; i < 1000; i++) 
	{
		auto [a, b, _] = distances[i];

		if(indexChanges[a] != indexChanges[b])
		{ // if not in the same set
			auto rootB = indexChanges[b];
			for(auto index : linkedIndices[rootB])
			{
				indexChanges[index] = indexChanges[a];
				linkedIndices[indexChanges[a]].insert(index);
			}
			linkedIndices[rootB].clear();
		}
	}

	auto indexValues = linkedIndices 
						| views::values 
						| views::transform([](auto&& x){ return x.size(); })
						| ranges::to<vector>();
	partial_sort(indexValues.begin(), indexValues.begin() + 3, indexValues.end(), greater<int>());

	ll prod = 1;
	for(int i = 0; i < 3; i++) prod *= indexValues[i];

	cout << prod << endl;

	return 0;
}