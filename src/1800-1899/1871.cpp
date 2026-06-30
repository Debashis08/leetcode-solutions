/*
Tags

array, dp, bfs

Problem Description

1871. Jump Game VII
You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:

i + minJump <= j <= min(i + maxJump, s.length - 1), and
s[j] == '0'.
Return true if you can reach index s.length - 1 in s, or false otherwise.

Example 1:
Input: s = "011010", minJump = 2, maxJump = 3
Output: true
Explanation:
In the first step, move from index 0 to index 3.
In the second step, move from index 3 to index 5.

Example 2:
Input: s = "01101110", minJump = 2, maxJump = 3
Output: false

Constraints:
2 <= s.length <= 105
s[i] is either '0' or '1'.
s[0] == '0'
1 <= minJump <= maxJump < s.length

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
using namespace std;


// solution using bfs and maximum reached index approach
class Solution1
{
public:
	bool canReach(string s, int minJump, int maxJump)
	{
		int n = s.size();
		if (s[n - 1] == 1)
		{
			return false;
		}
		int furthest = 0;
		vector<bool> visited(n, false);
		queue<int> q;
		q.push(0);

		visited[0] = true;
		while (!q.empty())
		{
			int index = q.front();
			q.pop();

			if (index == n - 1)
			{
				return true;
			}
			int start = max(index + minJump, furthest + 1);
			int end = min(index + maxJump, n - 1);

			for (int i = start; i <= end; i++)
			{
				if (s[i] == '0' && !visited[i])
				{
					visited[i] = true;
					q.push(i);
				}
			}
			furthest = max(end, furthest);
		}

		return false;
	}
};

// solution using dp and sliding window approach
class Solution2 {
public:
	bool canReach(string s, int minJump, int maxJump) {
		int n = s.size();
		if (s[n - 1] == '1')
		{
			return false;
		}
		vector<bool> dp(n, false);
		int activeCount = 0;
		dp[0] = true;

		for (int i = 1; i < n; i++)
		{
			if (i >= minJump && dp[i - minJump])
			{
				activeCount++;
			}
			if (i > maxJump && dp[i - maxJump - 1])
			{
				activeCount--;
			}
			if (s[i] == '0' && activeCount > 0)
			{
				dp[i] = true;
			}
		}
		return dp[n - 1];
	}
};

int main()
{
	//Solution1 sol;
	Solution2 sol;
	string str;
	int minJump, maxJump;
	cin >> str >> minJump >> maxJump;

	cout << (sol.canReach(str, minJump, maxJump) == true ? "true" : "false");

	return 0;
}