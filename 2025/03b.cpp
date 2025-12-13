#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

long long pow10(long long n)
{
	long long r = 1;
	while(n-- > 0) r *= 10;
	return r;
}

int main()
{
	string s;
	long long sum = 0, voltage;
	vector<int> digits = vector<int>(12);

	int count = 1;

	int digitAdj;

	while (cin >> s)
	{
		digitAdj = 11;
		auto prevMaxIndex = s.begin() - 1;
		while(digitAdj >= 0)
		{
			auto maxIndex = max_element(prevMaxIndex + 1, s.end() - digitAdj);
			prevMaxIndex = maxIndex;
			digits[11-digitAdj--] = (int) *maxIndex - '0';
		}
		
		voltage = 0;
		for(int i = 0; i < digits.size(); i++) voltage += pow10(11-i) * digits[i];

		sum += voltage;
	}

	cout << sum << endl;

	return 0;
}