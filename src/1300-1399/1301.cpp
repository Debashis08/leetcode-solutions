/*
Tags
level-hard
array, dp, matrix

Problem Description
1301. Number of Paths with Max Score

You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.
You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'.
In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.
Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.
In case there is no path, return [0, 0].

Example 1:
Input: board = ["E23","2X2","12S"]
Output: [7,1]

Example 2:
Input: board = ["E12","1X1","21S"]
Output: [4,2]

Example 3:
Input: board = ["E11","XXX","11S"]
Output: [0,0]

Constraints:
2 <= board.length == board[i].length <= 100
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <limits>
#include <iomanip>
#include <functional>
#include <cstring>
#include <climits>
#include "../core/core.h"
using namespace std;

class Solution
{
private:
	static constexpr int mod = (int)1e9 + 7;
public:
	void update(vector<vector<pair<int, int>>>& dp, int n, int x, int y, int u, int v)
	{
		if (u >= n || v >= n || dp[u][v].first == -1)
		{
			return;
		}
		if (dp[u][v].first > dp[x][y].first)
		{
			dp[x][y] = dp[u][v];
		}
		else if (dp[u][v].first == dp[x][y].first)
		{
			dp[x][y].second += dp[u][v].second;
			if (dp[x][y].second >= mod)
			{
				dp[x][y].second -= mod;
			}
		}
	}

	vector<int> pathsWithMaxScore(vector<string>& board)
	{
		int n = board.size();
		vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, { -1,0 }));
		dp[n - 1][n - 1] = { 0, 1 };
		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = n - 1; j >= 0; j--)
			{
				if (!(i == n - 1 && j == n - 1) && (board[i][j] != 'X'))
				{
					this->update(dp, n, i, j, i + 1, j);
					this->update(dp, n, i, j, i, j + 1);
					this->update(dp, n, i, j, i + 1, j + 1);
					if (dp[i][j].first != -1)
					{
						dp[i][j].first += (board[i][j] == 'E' ? 0 : board[i][j] - '0');
					}
				}
			}
		}

		return dp[0][0].first == -1 ? vector<int>{0, 0} : vector<int>{ dp[0][0].first, dp[0][0].second };
	}
};

int main()
{
	int n;
	Solution sol;
	cin >> n;
	vector<string> board(n);
	for (int i = 0; i < n; i++)
	{
		cin >> board[i];
	}
	auto result = sol.pathsWithMaxScore(board);
	cout << result[0] << " " << result[1] << "\n";
	return 0;
}