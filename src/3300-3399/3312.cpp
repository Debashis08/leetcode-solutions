/*
Tags
level-hard
array, hash-table, math, binary-search, combinatorics, counting, number-theory, prefix-sum

Problem Description
3312. Sorted GCD Pair Queries

You are given an integer array nums of length n and an integer array queries.
Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.
For each query queries[i], you need to find the element at index queries[i] in gcdPairs.
Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.
The term gcd(a, b) denotes the greatest common divisor of a and b.

Example 1:
Input: nums = [2,3,4], queries = [0,2,2]
Output: [1,2,2]
Explanation:
gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
After sorting in ascending order, gcdPairs = [1, 1, 2].
So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].

Example 2:
Input: nums = [4,4,2,1], queries = [5,3,1,0]
Output: [4,2,1,1]
Explanation:
gcdPairs sorted in ascending order is [1, 1, 1, 2, 2, 4].

Example 3:
Input: nums = [2,2], queries = [0,0]
Output: [2,2]
Explanation:
gcdPairs = [2].

Constraints:
2 <= n == nums.length <= 10^5
1 <= nums[i] <= 5 * 10^4
1 <= queries.length <= 10^5
0 <= queries[i] < n * (n - 1) / 2
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
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries)
    {
        int m = *max_element(nums.begin(), nums.end());
        vector<long long> count(m + 1);
        for (int num : nums)
        {
            count[num]++;
        }

        for (int i = 1; i <= m; i++)
        {
            for (int j = i * 2; j <= m; j += i)
            {
                count[i] += count[j];
            }
        }

        for (int i = 1; i <= m; i++)
        {
            count[i] = count[i] * (count[i] - 1) / 2;
        }

        for (int i = m; i >= 1; i--)
        {
            for (int j = i * 2; j <= m; j += i)
            {
                count[i] -= count[j];
            }
        }

        for (int i = 1; i <= m; i++)
        {
            count[i] += count[i - 1];
        }

        vector<int> result;
        for (long long q : queries)
        {
            q++;
            int pos = lower_bound(count.begin(), count.end(), q) - count.begin();
            result.push_back(pos);
        }

        return result;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    vector<long long> queries(m);

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    for (int i = 0; i < m; i++)
    {
        cin >> queries[i];
    }

    Solution sol;
    vector<int> result = sol.gcdValues(nums, queries);
    Core::printVectorResult(result);
	return 0;
}