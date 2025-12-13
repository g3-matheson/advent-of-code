#include <iostream>
#include <format>
#include <vector>

using namespace std;
using ll = long long;

int main()
{
	string s;
	vector<int> nums;
	vector<char> ops;

	ll colSum = 0, sum = 0;

	while(cin >> s)
	{
		if(s == "+" || s == "*") ops.push_back(s[0]);
		else nums.push_back(stoi(s));
	}

	cout << format("ops.size = {}, nums.size = {}", ops.size(), nums.size()) << endl;
	
	for(int i = 0; i < ops.size(); i++)
	{
		colSum = ops[i] == '+' ? 0 : 1;

		vector<int> indices = { i, i + 1000, i + 2000, i + 3000};
		for(auto ind : indices)
		{
			if (ops[i] == '+') colSum += nums[ind];
			else colSum *= nums[ind];
		}
		sum += colSum;
	}

	cout << sum << endl;

	return 0;
}