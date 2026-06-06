/*
Tags
level-easy
array, prefix-sum

Problem Description
2574. Left and Right Sum Differences
You are given a 0-indexed integer array nums of size n.
Define two arrays leftSum and rightSum where:
leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element, leftSum[i] = 0.
rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element, rightSum[i] = 0.
Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.

Example 1:
Input: nums = [10,4,8,3]
Output: [15,1,11,22]
Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].

Example 2:
Input: nums = [1]
Output: [0]
Explanation: The array leftSum is [0] and the array rightSum is [0].
The array answer is [|0 - 0|] = [0].

Constraints:
1 <= nums.length <= 1000
1 <= nums[i] <= 10^5

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
#include "../../core/core.h"
using namespace std;

class Solution {
public:
	vector<int> leftRightDifference(vector<int>& nums) {
		long rightSum = accumulate(nums.begin() + 1, nums.end(), 0);
		vector<int> result(nums.size());
		int ls = 0;
		int rs = rightSum;
		for (int i = 0; i < nums.size(); i++)
		{
			result[i] = abs(ls - rs);
			if (i < nums.size() - 1)
			{
				ls += nums[i];
				rs -= nums[i + 1];
			}
		}

		return result;
	}
};

int main()
{
	int n, x;
	vector<int> nums;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		nums.push_back(x);
	}

	Solution sol;
	vector<int> result = sol.leftRightDifference(nums);
	Core::printVectorResult(result);
	return 0;
}