#include <iostream>
#include <ranges>
#include <vector>

using namespace std;
using ll = long long;

/*
	Input:
	0-5: present shapes (. = empty space)
	nxm: a b c d e f
	n wide, m high, # of each present

	Presents can be rotated and flipped.

	How many regions can fit the presents listed?

	A greedy and naive approach works, although it shouldn't:
		- for each line of input:
		- add (# of present_i) * (# of spaces present_i takes up)
		- if this number is less than the area, add 1 to count
*/

int main()
{
	string s;
	ll count = 0;
	vector<int> presentSpace = {7, 7, 7, 7, 6, 5};

	while(getline(cin, s))
	{
		vector<string> mults = s.substr(0, s.find(':')) | views::split('x') | views::transform([](auto&& x){ return string(x.begin(), x.end()); }) | ranges::to<vector>();
		ll constraint = (stoll(mults[0]) * stoll(mults[1]));

		ll product = 0;
		
		int index = s.find(':')+2; 
		for(int i = 0; i < 6; i++)
		{
			product += stoll(s.substr(index, 2)) * presentSpace[i];
			index += 3;
		}	

		if (product < constraint) count++;
	}

	cout << count << endl;
	return 0;
}