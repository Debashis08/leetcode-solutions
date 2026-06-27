/*
Tags
level-hard
dp, prefix-sum

Problem Description
3699. Number of ZigZag Arrays I
You are given three integers n, l, and r.
A ZigZag array of length n is defined as follows:
Each element lies in the range [l, r].
No two adjacent elements are equal.
No three consecutive elements form a strictly increasing or strictly decreasing sequence.
Return the total number of valid ZigZag arrays.
Since the answer may be large, return it modulo 109 + 7.
A sequence is said to be strictly increasing if each element is strictly greater than its previous one (if exists).
A sequence is said to be strictly decreasing if each element is strictly smaller than its previous one (if exists).

Example 1:
Input: n = 3, l = 4, r = 5
Output: 2
Explanation:
There are only 2 valid ZigZag arrays of length n = 3 using values in the range [4, 5]:
[4, 5, 4]
[5, 4, 5]​​​​​​​

Example 2:
Input: n = 3, l = 1, r = 3
Output: 10
Explanation:
There are 10 valid ZigZag arrays of length n = 3 using values in the range [1, 3]:
[1, 2, 1], [1, 3, 1], [1, 3, 2]
[2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
[3, 1, 2], [3, 1, 3], [3, 2, 3]
All arrays meet the ZigZag conditions.

Constraints:
3 <= n <= 2000
1 <= l < r <= 2000

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

constexpr int MOD = 1e9 + 7;
class Solution
{
public:
    int zigZagArrays(int n, int l, int r)
    {
        int m = r - l + 1;
        vector<int> dp0(m, 1);
        vector<int> dp1(m, 1);
        vector<int> sum0(m + 1, 0);
        vector<int> sum1(m + 1, 0);

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                sum0[j + 1] = (sum0[j] + dp0[j]) % MOD;
                sum1[j + 1] = (sum1[j] + dp1[j]) % MOD;
            }

            for (int j = 0; j < m; j++)
            {
                dp0[j] = (sum1[m] - sum1[j + 1] + MOD) % MOD;
                dp1[j] = sum0[j];
            }
        }

        auto op = [](int acc, int x) {
            return (acc + x) % MOD;
            };
        auto ans0 = reduce(dp0.begin(), dp0.end(), 0, op);
        auto ans1 = reduce(dp1.begin(), dp1.end(), 0, op);

        return (ans0 + ans1) % MOD;
    }
};

int main()
{
    int n, l, r;
    cin >> n >> l >> r;
    Solution sol;
    int result = sol.zigZagArrays(n, l, r);
    cout << result << "\n";
	return 0;
}