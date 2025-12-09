#include <algorithm>
#include <iostream>
#include <format>
#include <ranges>
#include <vector>

using namespace std;
using ll = long long;

long long pow10(long long n)
{
	long long r = 1;
	while(n-- > 0) r *= 10;
	return r;
}

int main()
{
	string s;
	vector<string> rawInput;
	vector<vector<string>> nums = vector<vector<string>>(4, vector<string>());
	vector<char> ops;

	ll colSum = 0, sum = 0;
	size_t index;

	// need to do input per line and account for spacing to know how numbers are aligned
	for(int i = 0; i < 4; i++)
	{
		getline(cin, s);
		rawInput.push_back(s);
	}

	index = 1;
	while(index < s.size())
	{
		int spaceIndex = ranges::max(rawInput | views::transform([index](const string& x)
							{
								return x.find(' ', index);
							}));
		if(spaceIndex == -1) break;
		
		for(auto& in : rawInput)
		{
			for(int i = index; i < spaceIndex; i++)
			{
				if(in[i] == ' ') in[i] = '0';
			}
		}

		index = spaceIndex + 1;
	}

	for(int i = 0; i < rawInput.size(); i++)
	{
		auto& in = rawInput[i];
		for(int j = index; j < s.size(); j++)
		{
			if(in[j] == ' ') in[j] = '0';
		}
		
		for(const auto& x : views::split(in, ' '))
		{
			nums[i].emplace_back(x.begin(), x.end());
		}
		cout << in << endl;
	}

	while(cin >> s) 
	{
		ops.push_back(s[0]);
		cout << s[0] << " ";
	}
	cout << endl;
	
	for(int i = 0; i < ops.size(); i++)
	{
		colSum = ops[i] == '+' ? 0 : 1;

		auto digits = nums[0][i].size();
		for(int d = 0; d < digits; d++)
		{
			auto assembledNum = 0;
			auto pow = 0;
			bool foundDigit = false;
			for(int j = 0; j < 4; j++)
			{
				if(nums[j][i][d] != '0' && !foundDigit) 
				{
					pow = 3-j;
					foundDigit = true;
				}
				else if(nums[j][i][d] == '0' && foundDigit) 
				{
					pow = j-1;
					break;
				}
			}

			for(int j = 0; j < 4; j++)
			{
				if(nums[j][i][d] == '0') continue;
				assembledNum += ((int) nums[j][i][d] - '0') * pow10(pow--);
			}

			if(ops[i] == '+') colSum += assembledNum;
			else colSum *= assembledNum;
		}

		sum += colSum;
	}

	cout << sum << endl;

	return 0;
}