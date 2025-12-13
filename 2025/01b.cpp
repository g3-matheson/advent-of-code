#include <iostream>
using namespace std;

/*
	Dial has numbers 0 to 99
	Starts at 50
	LX means rotate left by X positions
	RX means rotate right by X positions
	The output should be the number of times the dial points at 0 or passes 0
*/

int main()
{
	int dial = 50, dialMax = 100, password = 0, sign, move;

	string s;
	while (cin >> s)
	{
		sign = s[0] == 'L' ? -1 : 1;
		move = stoi(s.substr(1));
		
		password += move / 100;
		move -= 100 * (move/100);

		if(dial != 0 && move != 0 && (sign == -1 && move >= dial || sign == 1 && move >= 100-dial)) password++;

		dial = (dial + sign * move + 100) % 100;
	}

	cout << password << endl;
	return 0;
}