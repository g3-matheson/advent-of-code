#include <iostream>
#include <format>
#include <vector>

using namespace std;

pair<int,int> operator+(const pair<int,int>& a, const pair<int,int>& b)
{
	return { a.first + b.first, a.second + b.second };
}

int main()
{
	string s;
	int count = 0, accessible = 0;
	int n = 136, m;
	vector<vector<char>> grid = vector<vector<char>>(n);
	vector<pair<int,int>> directions = { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1} };

	// input
	while(cin >> s)
	{
		for(char c : s) grid[count].push_back(c);
		count++;
	}

	m = grid[0].size();

	bool removed = true;

	while(removed)
	{
		removed = false;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(grid[i][j] == '.' || grid[i][j] == 'X') continue;
				count = 0;
				for(auto dir : directions)
				{
					auto nei = make_pair(i,j) + dir;
					if(nei.first < 0 || nei.first >= m || nei.second < 0 || nei.second >= n) continue;
					if(grid[nei.first][nei.second] == '@') count++;
					if(count >= 4) break;
				}

				if(count < 4)
				{
					grid[i][j] = 'X';
					removed = true;
					accessible++;
				}
			}
		}
	}

	cout << accessible << endl;

	return 0;
}