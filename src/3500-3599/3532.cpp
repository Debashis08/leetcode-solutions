/*
Tags
level-medium
array, hash-table, binary-search, union-find, graph

Problem Description
3532. Path Existence Queries in a Graph I

You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.
An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.
Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.

Example 1:
Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]
Output: [true,false]
Explanation:
Query [0,0]: Node 0 has a trivial path to itself.
Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
Thus, the final answer after processing all the queries is [true, false].

Example 2:
Input: n = 4, nums = [2,5,6,8], maxDiff = 2, queries = [[0,1],[0,2],[1,3],[2,3]]
Output: [false,false,true,true]
Explanation:
The resulting graph is:
Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |2 - 5| = 3, which is greater than maxDiff.
Query [0,2]: There is no edge between Node 0 and Node 2 because |nums[0] - nums[2]| = |2 - 6| = 4, which is greater than maxDiff.
Query [1,3]: There is a path between Node 1 and Node 3 through Node 2 since |nums[1] - nums[2]| = |5 - 6| = 1 and |nums[2] - nums[3]| = |6 - 8| = 2, both of which are within maxDiff.
Query [2,3]: There is an edge between Node 2 and Node 3 because |nums[2] - nums[3]| = |6 - 8| = 2, which is equal to maxDiff.
Thus, the final answer after processing all the queries is [false, false, true, true].

Constraints:
1 <= n == nums.length <= 10^5
0 <= nums[i] <= 10^5
nums is sorted in non-decreasing order.
0 <= maxDiff <= 10^5
1 <= queries.length <= 10^5
queries[i] == [ui, vi]
0 <= ui, vi < n
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

class DisjointSetUnion
{
private:
    vector<int> parent;
public:
    DisjointSetUnion(int n)
    {
        // Make each node it's own parent.
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void link(int x, int y)
    {
        int parentX = this->find(x);
        int parentY = this->find(y);
        parent[parentX] = parentY;
    }
};

class Solution
{
public:

    // Approach 1: Assigning component numbers(this is the optimal solution in this case as the nums array is sorted in non-decreasing order)
    vector<bool> pathExistenceQueriesImplementation01(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries)
    {
        vector<int> component(n, 0);
        int componentNo = 0;
        for (int i = 1; i < n; i++)
        {
            if (nums[i] - nums[i - 1] > maxDiff)
            {
                componentNo++;
            }
            component[i] = componentNo;
        }

        vector<bool> result;
        for (auto& query : queries)
        {
            result.push_back(component[query[0]] == component[query[1]]);
        }

        return result;
    }

    // Approach 2: Using Disjoint Set Union to find the components (this method is applicable even in the case when the nums array is not sorted)
    vector<bool> pathExistenceQueriesImplementation02(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries)
    {
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < n; i++)
        {
            pq.push({ nums[i], i });
        }

        DisjointSetUnion dsu(n);

        pair<int, int> temp = pq.top();

        while (!pq.empty())
        {
            auto& curr = pq.top();
            pq.pop();
            if (abs(temp.first - curr.first) <= maxDiff)
            {
                dsu.link(temp.second, curr.second);
            }
            temp = curr;
        }

        vector<bool> result;
        for (auto& query : queries)
        {
            result.push_back(dsu.find(query[0]) == dsu.find(query[1]));
        }

        return result;
    }
};

int main()
{
    int n, maxDiff, m;
    cin >> n >> maxDiff >> m;
    vector<int> nums(n, 0);
    vector<vector<int>> queries(m, vector<int>(2, 0));
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }
    Solution sol;
    //vector<bool> result = sol.pathExistenceQueriesImplementation01(n, nums, maxDiff, queries);
    vector<bool> result = sol.pathExistenceQueriesImplementation02(n, nums, maxDiff, queries);
    Core::printVectorResult(result);
	return 0;
}