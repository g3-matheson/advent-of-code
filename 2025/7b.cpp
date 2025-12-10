#include <iostream>
#include <unordered_map>

using namespace std;
using ll = long long;

int main()
{
	// count # of alternate timelines
	// means we need to keep track of how many paths

	string s;
	cin >> s;

	int S = s.find('S');
	unordered_map<int,ll> paths = { {S, 1} };

	int parity = 1;
	while(cin >> s)
	{
		if(parity++ % 2 == 1) continue;

		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '^' && paths.contains(i))
			{
				paths[i-1] += paths[i];
				paths[i+1] += paths[i];
				paths[i] = 0;
			}
		}
	}

	ll sum = 0;
	for(auto kvp : paths) sum += kvp.second;

	cout << sum << endl;

	return 0;
}