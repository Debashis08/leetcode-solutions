/*
Tags
level-easy
array, math

Problem Description
3300. Minimum Element After Replacement With Digit Sum
You are given an integer array nums.
You replace each element in nums with the sum of its digits.
Return the minimum element in nums after all replacements.

Example 1:
Input: nums = [10,12,13,14]
Output: 1
Explanation:
nums becomes [1, 3, 4, 5] after all replacements, with minimum element 1.

Example 2:
Input: nums = [1,2,3,4]
Output: 1
Explanation:
nums becomes [1, 2, 3, 4] after all replacements, with minimum element 1.

Example 3:
Input: nums = [999,19,199]
Output: 10
Explanation:
nums becomes [27, 10, 19] after all replacements, with minimum element 10.

Constraints:
1 <= nums.length <= 100
1 <= nums[i] <= 10^4

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
#include<cstring>
#include<climits>
using namespace std;


class Solution {
public:
	int minElement(vector<int>& nums) {
		int result = INT_MAX;
		for (int num : nums)
		{
			int sum = 0;
			while (num)
			{
				sum += (num % 10);
				num /= 10;
			}
			result = min(result, sum);
		}

		return result;
	}
};

int main()
{
	int n;
	vector<int> vec;
	cin >> n;
	int x;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		vec.push_back(x);
	}
	Solution sol;
	cout << sol.minElement(vec);

	return 0;
}