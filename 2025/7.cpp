#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
	int splits = 0;

	// keep track of beam by column #
	unordered_set<int> beams, newBeams;
	
	string s;
	cin >> s;

	beams.insert(s.find('S'));
	newBeams.insert(s.find('S'));

	int parity = 1;
	while(cin >> s)
	{
		if (parity++ % 2 == 1) continue; // skip lines with no splitters

		for(int i = 0; i < s.size(); i++)
		{
			if(s[i] == '^' && beams.contains(i))
			{
				newBeams.erase(i);
				newBeams.insert(i-1);
				newBeams.insert(i+1);
				splits++;
			}
		}

		beams = unordered_set<int>(newBeams.begin(), newBeams.end());
	}

	cout << splits << endl;

	return 0;
}