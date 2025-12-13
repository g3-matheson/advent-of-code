#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int main()
{
	string s;
	int sum = 0, max, adj, count = 1;

	while (cin >> s)
	{
		auto maxIndex = s.end();
		auto secondMaxIndex = s.end();
		adj = 0;
		while (true)
		{
			maxIndex = max_element(s.begin(), s.end() - adj);
			secondMaxIndex = max_element(maxIndex + 1, s.end());
			if (maxIndex == s.end()-1) adj++;
			else break;
		}
		
		int max = 10*((int) *maxIndex - '0') + (int) *secondMaxIndex - '0';
		sum += max;
	}

	cout << sum << endl;

	return 0;
}