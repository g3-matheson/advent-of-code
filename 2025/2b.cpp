#include <iostream>
#include <format>
#include <string>
#include <vector>
#include <ranges>
#include <unordered_set>

using namespace std;

/*
	Day 2: "Gift Shop"
	Input file contains product ID ranges left to check
	Invalid IDs are made of a number repeated AT LEAST twice, or that start with 0
*/

static int debug = 2;

long long pow10(long long n)
{
	long long r = 1;
	while(n-- > 0) r *= 10;
	return r;
}

string operator*(string s, long long m)
{
	string out = "";
	for(int i = 0; i < m; i++) out += s;
	return out;
}

int main()
{
	string s, is; 
	long long minus, a, b, n, m, l, r, ml, mr, num, sum = 0;
	unordered_set<long long> seen;

	cin >> s;

	auto splitview = views::split(s, ',')
					| views::transform([](auto&& x){ return string(x.begin(), x.end()); });

	for (auto sp : splitview) // read in each line
	{
		// get range a-b
		minus = sp.find('-');
		a = stoll(sp.substr(0, minus));
		b = stoll(sp.substr(minus+1));
		
		// lengths of a,b
		n = minus;
		m = sp.size() - minus - 1; 

		if(debug > 1) cout << format("sp = {}, minus = {}, a = {}, b = {}, n = {}, m = {}", sp, minus, a, b, n, m) << endl;

		// check repeated strings of length 1..m/2
		for (long long div = 1; div <= m/2; div++)
		{
			// early short-circuit
			if (n == m && n % div != 0) continue;

			// ml = multiplicity of left limit
			// mr = multiplicity of right limit
			ml = n % div == 0 ? n / div : n / div + 1;
			mr = m / div;
			if(ml > mr) continue; 

			// l = number to start testing at, lower bound
				// if n % div == 0 then just take first div digits
				// otherwise start at 10^{div-1} e.g: 244 / 2 => start at 10^1 = 10 (i.e start looking at 1010)
			l = n % div == 0 ? stoll(sp.substr(0, div)) : pow10(div-1);
			r = m % div == 0 ? stoll(sp.substr(minus+1, div)) : pow10(div) - 1;
		
			// case where mr > ml has to be handled differently since we can have l > r
			if(ml == mr)
			{
				for(long long i = l; i <= r; i++)
				{
					is = to_string(i);
					num = stoll(is * ml);
					if (num >= a && num <= b)
					{
						auto result = seen.insert(num);
						if(result.second) 
						{
							sum += num;
							if(debug > 0) cout << format("div = {}, l = {}, ml = {}, r = {}, mr = {}, num = {}", div, l, ml, r, mr, num) << endl;
						}
					}
				}
			}
			else if(mr > ml)
			{
				// causes issues when n = 1 and ml = 1
				if(ml > 1)
				{
					for(long long i = l; i < pow10(div); i++)
					{
						is = to_string(i);
						num = stoll(is * ml);
						if (num >= a && num <= b)
						{
							auto result = seen.insert(num);
 							if(result.second) 
							{
								sum += num;
								if(debug > 0) cout << format("div = {}, l = {}, ml = {}, r = {}, mr = {}, num = {}", div, l, ml, r, mr, num) << endl;
							}
						}
					}
				}
			
				for(long long i = r; i >= pow10(div-1); i--)
				{
					is = to_string(i);
					num = stoll(is * mr);
					if (num >= a && num <= b)
					{
						auto result = seen.insert(num);
 						if(result.second) 
						{
							sum += num;
							if(debug > 0) cout << format("div = {}, l = {}, ml = {}, r = {}, mr = {}, num = {}", div, l, ml, r, mr, num) << endl;
						}
					}
				}
			}
			
		}
	}

	cout << sum << endl;

	return 0;
}