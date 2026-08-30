/*
Tags
level-medium
array, greedy

Problem Description
2091. Removing Minimum and Maximum From Array

You are given a 0-indexed array of distinct integers nums.
There is an element in nums that has the lowest value and an element that has the highest value. We call them the minimum and maximum respectively. 
Your goal is to remove both these elements from the array.
A deletion is defined as either removing an element from the front of the array or removing an element from the back of the array.
Return the minimum number of deletions it would take to remove both the minimum and maximum element from the array.

Example 1:
Input: nums = [2,10,7,5,4,1,8,6]
Output: 5
Explanation:
The minimum element in the array is nums[5], which is 1.
The maximum element in the array is nums[1], which is 10.
We can remove both the minimum and maximum by removing 2 elements from the front and 3 elements from the back.
This results in 2 + 3 = 5 deletions, which is the minimum number possible.

Example 2:
Input: nums = [0,-4,19,1,8,-2,-3,5]
Output: 3
Explanation:
The minimum element in the array is nums[1], which is -4.
The maximum element in the array is nums[2], which is 19.
We can remove both the minimum and maximum by removing 3 elements from the front.
This results in only 3 deletions, which is the minimum number possible.

Example 3:
Input: nums = [101]
Output: 1
Explanation:
There is only one element in the array, which makes it both the minimum and maximum element.
We can remove it with 1 deletion.

Constraints:
1 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
The integers in nums are distinct.
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
    int minimumDeletions(vector<int>& nums) {
        // Total number of elements.
        int n = nums.size();

        // Find the indices of min and max elements.
        int minElementIndex = min_element(nums.begin(), nums.end()) - nums.begin();
        int maxElementIndex = max_element(nums.begin(), nums.end()) - nums.begin();

        // Find the left(min) and right(max) indices to calculate the number of deletions in 3 cases.
        int left = min(minElementIndex, maxElementIndex);
        int right = max(minElementIndex, maxElementIndex);

        // Return the min number of deletions, for all 3 cases,
        // 1. deleting from start -> total number of deletions = right+1
        // 2. deleting from end -> total number of deleltions = n-left
        // 3. deleting from start and end -> total number of deletions = left+1+n-right
        return min({ right + 1, n - left, left + 1 + n - right });
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
    int result = sol.minimumDeletions(nums);
    cout << result << "\n";
	return 0;
}