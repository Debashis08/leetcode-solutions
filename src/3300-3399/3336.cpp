/*
Tags
level-hard
array, math, dp, number-theory

Problem Description
3336. Find the Number of Subsequences With Equal GCD

You are given an integer array nums.
Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
Return the total number of such pairs.
Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: nums = [1,2,3,4]
Output: 10
Explanation:
The subsequence pairs which have the GCD of their elements equal to 1 are:
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])
([1, 2, 3, 4], [1, 2, 3, 4])

Example 2:
Input: nums = [10,20,30]
Output: 2
Explanation:
The subsequence pairs which have the GCD of their elements equal to 10 are:
([10, 20, 30], [10, 20, 30])
([10, 20, 30], [10, 20, 30])

Example 3:
Input: nums = [1,1,1,1]
Output: 50

Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= 200
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
	static constexpr int mod = 1e9 + 7;
public:
	int subsequencePairCount(vector<int>& nums)
	{
		int m = *max_element(nums.begin(), nums.end());
		int n = nums.size();

		vector<vector<int>> dp(m + 1, vector<int>(m + 1));
		dp[0][0] = 1;

		for (int num : nums)
		{
			vector<vector<int>> ndp(m + 1, vector<int>(m + 1));
			for (int j = 0; j <= m; j++)
			{
				int divisor1 = gcd(j, num);
				for (int k = 0; k <= m; k++)
				{
					int val = dp[j][k];
					if (val == 0)
					{
						continue;
					}

					int divisor2 = gcd(k, num);
					ndp[j][k] = (ndp[j][k] + val) % mod;
					ndp[divisor1][k] = (ndp[divisor1][k] + val) % mod;
					ndp[j][divisor2] = (ndp[j][divisor2] + val) % mod;
				}
			}
			dp.swap(ndp);
		}

		int result = 0;
		for (int j = 1; j <= m; j++)
		{
			result = (result + dp[j][j]) % mod;
		}

		return result;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<int> nums(n, 0);
	Solution sol;
	for (int i = 0; i < n; i++)
	{
		cin >> nums[i];
	}
	int result = sol.subsequencePairCount(nums);
	cout << result << "\n";
	return 0;
}