/*
Tags
level-medium
array, math, bit-manipulation, enumeration

Problem Description
3514. Number of Unique XOR Triplets II

You are given an integer array nums.
A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
Return the number of unique XOR triplet values from all possible triplets (i, j, k).

Example 1:
Input: nums = [1,3]
Output: 2
Explanation:
The possible XOR triplet values are:
(0, 0, 0) → 1 XOR 1 XOR 1 = 1
(0, 0, 1) → 1 XOR 1 XOR 3 = 3
(0, 1, 1) → 1 XOR 3 XOR 3 = 1
(1, 1, 1) → 3 XOR 3 XOR 3 = 3
The unique XOR values are {1, 3}. Thus, the output is 2.

Example 2:
Input: nums = [6,7,8,9]
Output: 4
Explanation:
The possible XOR triplet values are {6, 7, 8, 9}. Thus, the output is 4.

Constraints:
1 <= nums.length <= 1500
1 <= nums[i] <= 1500
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

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int maxVal = *max_element(nums.begin(), nums.end());
        int u = 1;
        while (u <= maxVal)
        {
            u <<= 1;
        }

        vector<int> s(u);
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                s[nums[i] ^ nums[j]] = 1;
            }
        }

        vector<int> t(u);
        for (int x = 0; x < u; x++)
        {
            if (!s[x])
            {
                continue;
            }
            for (int v : nums)
            {
                t[x ^ v] = 1;
            }
        }

        int result = 0;
        for (int x = 0; x < u; x++)
        {
            if (t[x])
            {
                result++;
            }
        }

        return result;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    Solution sol;
    int result = sol.uniqueXorTriplets(nums);
    cout << result << "\n";
    return 0;
}