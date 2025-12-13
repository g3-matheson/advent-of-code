#include <iostream>
#include <string>
#include <vector>
#include <ranges>

using namespace std;

/*
	Day 2: "Gift Shop"
	Input file contains product ID ranges left to check
	Invalid IDs are made of a number repeated twice, or that start with 0
*/

long long pow10(long long n)
{
	long long r = 1;
	while(n-- > 0) r *= 10;
	return r;
}

int main()
{
	string s, is; 
	cin >> s;
	long long minus, a, b, n, m, l, r, num, sum = 0;

	auto splitview = views::split(s, ',')
					| views::transform([](auto&& x){ return string(x.begin(), x.end()); });

	for(auto sp : splitview)
	{
		minus = sp.find('-');
		a = stoll(sp.substr(0, minus));
		b = stoll(sp.substr(minus+1));
		
		n = minus;
		m = sp.size() - minus - 1;

		if(n == m && n % 2 != 0) continue;
		l = n % 2 == 0 ? stoll(sp.substr(0, n/2)) : pow10(n/2);
		r = m % 2 == 0 ? stoll(sp.substr(minus+1, m/2)) : pow10(m/2) - 1;
		
		for(long long i = l; i <= r; i++)
		{
			is = to_string(i);
			num = stoll(is + is);
			if (num >= a && num <= b) sum += num;
		}

	}

	cout << sum << endl;

	return 0;
}