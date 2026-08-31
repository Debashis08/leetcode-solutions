/*
Tags
level-medium
array, union-find, sorting

Problem Description
2948. Make Lexicographically Smallest Array by Swapping Elements

You are given a 0-indexed array of positive integers nums and a positive integer limit.
In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
Return the lexicographically smallest array that can be obtained by performing the operation any number of times.
An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. 
For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.

Example 1:
Input: nums = [1,5,3,9,8], limit = 2
Output: [1,3,5,8,9]
Explanation: Apply the operation 2 times:
- Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
- Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
We cannot obtain a lexicographically smaller array by applying any more operations.
Note that it may be possible to get the same result by doing different operations.

Example 2:
Input: nums = [1,7,6,18,2,1], limit = 3
Output: [1,6,7,18,1,2]
Explanation: Apply the operation 3 times:
- Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
- Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
- Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
We cannot obtain a lexicographically smaller array by applying any more operations.

Example 3:
Input: nums = [1,7,28,19,10], limit = 3
Output: [1,7,28,19,10]
Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= limit <= 10^9
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
#include <bitset>
#include <ranges>
#include "../core/core.h"
using namespace std;

class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store values with their original indices.
        vector<pair<int, int>> sortedNums(n);
        for (int i = 0; i < n; i++)
        {
            sortedNums[i] = { nums[i], i };
        }

        // Sort by values.
        sort(sortedNums.begin(), sortedNums.end());

        vector<int> result(n);
        int i = 0;

        while (i < n)
        {
            int j = i + 1;

            // Expand the current group as long as the difference is within the limit.
            while (j < n && sortedNums[j].first - sortedNums[j - 1].first <= limit)
            {
                j++;
            }

            // Collect thge original indices for the current group.
            vector<int> groupIndices;
            for (int k = i; k < j; k++)
            {
                groupIndices.push_back(sortedNums[k].second);
            }

            // Sort indices so we can place the smallest values at the earliest available spots.
            sort(groupIndices.begin(), groupIndices.end());

            // Map the sorted values to the sorted indices.
            for (int k = 0; k < groupIndices.size(); k++)
            {
                result[groupIndices[k]] = sortedNums[i + k].first;
            }

            // Move to the next group.
            i = j;
        }

        return result;
    }
};

int main()
{
    int n, limit;
    cin >> n >> limit;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    Solution sol;
    vector<int> result = sol.lexicographicallySmallestArray(nums, limit);
    Core::printVectorResult(result);
	return 0;
}