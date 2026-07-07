/*
Tags
level-easy
math

Problem Description
3754. Concatenate Non-Zero Digits and Multiply by Sum I

You are given an integer n.
Form a new integer x by concatenating all the non-zero digits of n in their original order. If there are no non-zero digits, x = 0.
Let sum be the sum of digits in x.
Return an integer representing the value of x * sum.

Example 1:
Input: n = 10203004
Output: 12340
Explanation:
The non-zero digits are 1, 2, 3, and 4. Thus, x = 1234.
The sum of digits is sum = 1 + 2 + 3 + 4 = 10.
Therefore, the answer is x * sum = 1234 * 10 = 12340.

Example 2:
Input: n = 1000
Output: 1
Explanation:
The non-zero digit is 1, so x = 1 and sum = 1.
Therefore, the answer is x * sum = 1 * 1 = 1.

Constraints:
0 <= n <= 10^9
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
public:
	long long sumAndMultiply(int n)
	{
		string value = to_string(n);
		long long sum = 0;
		long long x = 0;
		for (auto& c : value)
		{
			int d = c - '0';
			sum += d;
			if (d > 0)
			{
				x = x * 10 + d;
			}
		}

		return x * sum;
	}
};

int main()
{
	int n;
	cin >> n;
	Solution sol;
	long long result = sol.sumAndMultiply(n);
	cout << result << "\n";
	return 0;
}