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

	e.g for ranges:
	11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
	1698522-1698528,446443-446449,38593856-38593862,565653-565659,
	824824821-824824827,2121212118-2121212124

	Now we can repeat digits at least twice, so we have:
    
    11-22 still has two invalid IDs, 11 and 22.
    95-115 now has two invalid IDs, 99 and 111.
    998-1012 now has two invalid IDs, 999 and 1010.
    1188511880-1188511890 still has one invalid ID, 1188511885.
    222220-222224 still has one invalid ID, 222222.
    1698522-1698528 still contains no invalid IDs.
    446443-446449 still has one invalid ID, 446446.
    38593856-38593862 still has one invalid ID, 38593859.
    565653-565659 now has one invalid ID, 565656.
    824824821-824824827 now has one invalid ID, 824824824.
    2121212118-2121212124 now has one invalid ID, 2121212121.

	Add together all the invalid IDs for the output
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
	string sp, is; 
	long long minus, a, b, n, m, l, r, ml, mr, num, sum = 0;
	unordered_set<long long> seen;

	while (cin >> sp) // read in each line
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