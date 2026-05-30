/*
Tags
level-hard
array, binary-search, binary-indexed-tree, fenwick-tree, segment-tree

Problem Description
3161. Block Placement Queries
There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.
You are given a 2D array queries, which contains two types of queries:
For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x].
A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.

Example 1:
Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
Output: [false,true,true]
Explanation:
For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.

Example 2:
Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]
Output: [true,true,false]
Explanation:
Place an obstacle at x = 7 for query 0. A block of size at most 7 can be placed before x = 7.
Place an obstacle at x = 2 for query 2. Now, a block of size at most 5 can be placed before x = 7, and a block of size at most 2 before x = 2.


Constraints:
1 <= queries.length <= 15 * 104
2 <= queries[i].length <= 3
1 <= queries[i][0] <= 2
1 <= x, sz <= min(5 * 104, 3 * queries.length)
The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
The input is generated such that there is at least one query of type 2.

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
	vector<int> seg;
	void update(int index, int value, int p, int left, int right)
	{
		if (left == right)
		{
			seg[p] = value;
			return;
		}
		int mid = (left + right) >> 1;
		if (index <= mid)
		{
			update(index, value, p << 1, left, mid);
		}
		else
		{
			update(index, value, p << 1 | 1, mid + 1, right);
		}

		seg[p] = max(seg[p << 1], seg[p << 1 | 1]);
	}

	int query(int leftMost, int rightMost, int p, int left, int right)
	{
		if (leftMost <= left && right <= rightMost)
		{
			return seg[p];
		}
		int mid = (left + right) >> 1;
		int result = 0;
		if (leftMost <= mid)
		{
			result = max(result, query(leftMost, rightMost, p << 1, left, mid));
		}
		if (rightMost > mid)
		{
			result = max(result, query(leftMost, rightMost, p << 1 | 1, mid + 1, right));
		}

		return result;
	}

	vector<bool> getResults(vector<vector<int>>& queries) {
		int mx = 50000;
		seg.resize(mx << 2);
		set<int> st = { 0, mx };
		update(mx, mx, 1, 0, mx);
		vector<bool> result;

		for (auto& q : queries)
		{
			if (q[0] == 1)
			{
				int x = q[1];
				auto it = st.upper_bound(x);
				int right = *it;
				int left = *prev(it);
				update(x, x - left, 1, 0, mx);
				update(right, right - x, 1, 0, mx);
				st.insert(x);
			}
			else
			{
				int x = q[1];
				int sz = q[2];
				auto it = st.upper_bound(x);
				--it;
				int prev = *it;
				int maxSpace = query(0, prev, 1, 0, mx);
				maxSpace = max(maxSpace, x - prev);
				result.push_back(maxSpace >= sz);
			}
		}

		return result;
	}
};

int main()
{
	int n;
	cin >> n;
	int x;
	vector<vector<int>> queries;
	for (int i = 0; i < n; i++)
	{
		int m;
		cin >> m;
		vector<int> q;
		for (int j = 0; j < m; j++)
		{
			cin >> x;
			q.push_back(x);
		}
		queries.push_back(q);
	}
	Solution sol;
	vector<bool> result = sol.getResults(queries);
	Core::printVectorResult(result);
	return 0;
}