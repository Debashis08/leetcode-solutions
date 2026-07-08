/*
Tags
level-medium
math, string, prefix-sum

Problem Description
3756. Concatenate Non-Zero Digits and Multiply by Sum II

You are given a string s of length m consisting of digits. You are also given a 2D integer array queries, where queries[i] = [li, ri].
For each queries[i], extract the substring s[li..ri]. Then, perform the following:
Form a new integer x by concatenating all the non-zero digits from the substring in their original order. If there are no non-zero digits, x = 0.
Let sum be the sum of digits in x. The answer is x * sum.
Return an array of integers answer where answer[i] is the answer to the ith query.
Since the answers may be very large, return them modulo 109 + 7.

Example 1:
Input: s = "10203004", queries = [[0,7],[1,3],[4,6]]
Output: [12340, 4, 9]
Explanation:
s[0..7] = "10203004"
x = 1234
sum = 1 + 2 + 3 + 4 = 10
Therefore, answer is 1234 * 10 = 12340.
s[1..3] = "020"
x = 2
sum = 2
Therefore, the answer is 2 * 2 = 4.
s[4..6] = "300"
x = 3
sum = 3
Therefore, the answer is 3 * 3 = 9.

Example 2:
Input: s = "1000", queries = [[0,3],[1,1]]
Output: [1, 0]
Explanation:
s[0..3] = "1000"
x = 1
sum = 1
Therefore, the answer is 1 * 1 = 1.
s[1..1] = "0"
x = 0
sum = 0
Therefore, the answer is 0 * 0 = 0.

Example 3:
Input: s = "9876543210", queries = [[0,9]]
Output: [444444137]
Explanation:
s[0..9] = "9876543210"
x = 987654321
sum = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
Therefore, the answer is 987654321 * 45 = 44444444445.
We return 44444444445 modulo (109 + 7) = 444444137.

Constraints:
1 <= m == s.length <= 1^05
s consists of digits only.
1 <= queries.length <= 10^5
queries[i] = [li, ri]
0 <= li <= ri < m
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

const int mod = 1e9 + 7;
const int maxN = 100001;
long long pow10[maxN];

int init = []()
    {
        pow10[0] = 1;
        for (int i = 1; i < maxN; i++)
        {
            pow10[i] = (pow10[i - 1] * 10) % mod;
        }
        return 0;
    }();

class Solution
{
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries)
    {
        int n = s.size();
        vector<int> sum(n + 1, 0);
        vector<long long> x(n + 1, 0);
        vector<int> count(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            int d = s[i] - '0';
            sum[i + 1] = sum[i] + d;
            x[i + 1] = (d > 0) ? (x[i] * 10 + d) % mod : x[i];
            count[i + 1] = count[i] + (d > 0);
        }
        int m = queries.size();
        vector<int> result(m, 0);
        for (int i = 0; i < m; i++)
        {
            int l = queries[i][0];
            int r = queries[i][1] + 1;
            int length = count[r] - count[l];
            long long valX = (x[r] - x[l] * pow10[length] % mod + mod) % mod;
            long long valSum = sum[r] - sum[l];
            result[i] = (valX * valSum) % mod;
        }

        return result;
    }
};

int main()
{
    int m;
    string s;
    cin >> s >> m;
    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }
    Solution sol;
    vector<int> result = sol.sumAndMultiply(s, queries);
    Core::printVectorResult(result);
	return 0;
}