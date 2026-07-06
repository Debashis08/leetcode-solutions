/*
Tags
level-medium
array, sorting

Problem Description
1288. Remove Covered Intervals

Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are covered by another interval in the list.
The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.
Return the number of remaining intervals.

Example 1:
Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.

Example 2:
Input: intervals = [[1,4],[2,3]]
Output: 1

Constraints:
1 <= intervals.length <= 1000
intervals[i].length == 2
0 <= li < ri <= 10^5
All the given intervals are unique.
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
	int removeCoveredIntervals(vector<vector<int>>& intervals)
	{
		sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
			if (a[0] == b[0])
			{
				return a[1] > b[1];
			}
			return a[0] < b[0];
			});

		int count = 0;
		int maxEnd = 0;
		for (auto& interval : intervals)
		{
			if (interval[1] > maxEnd)
			{
				count++;
				maxEnd = interval[1];
			}
		}

		return count;
	}
};

int main()
{
	int n;
	Solution sol;
	cin >> n;
	vector<vector<int>> intervals(n, vector<int>(2, -1));
	for (int i = 0; i < n; i++)
	{
		cin >> intervals[i][0] >> intervals[i][1];
	}
	int result = sol.removeCoveredIntervals(intervals);
	cout << result << "\n";
	return 0;
}