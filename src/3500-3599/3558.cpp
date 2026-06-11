/*
Tags
level-medium
math, tree, bfs, dfs

Problem Description
3558. Number of Ways to Assign Edge Weights I
There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1.
The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.
Since the answer may be large, return it modulo 109 + 7.
Note: Ignore all edges not in the path from node 1 to x.

Example 1:
Input: edges = [[1,2]]
Output: 1
Explanation:
The path from Node 1 to Node 2 consists of one edge (1 → 2).
Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.

Example 2:
Input: edges = [[1,2],[1,3],[3,4],[3,5]]
Output: 2
Explanation:
The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node can be selected for processing.
For example, the path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4).
Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.

Constraints:
2 <= n <= 10^5
edges.length == n - 1
edges[i] == [ui, vi]
1 <= ui, vi <= n
edges represents a valid tree.

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

class Solution
{
private:
	int n;
	static constexpr int mod = 1e9 + 7;
	unordered_map<int, vector<int>> graph;
	int bfs()
	{
		int maxDepth = 0;
		queue<int> q;
		vector<int> distance(n + 1, -1);
		q.push(1);
		distance[1] = 0;
		maxDepth = distance[1];
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (auto& v : graph[u])
			{
				if (distance[v] == -1)
				{
					distance[v] = distance[u] + 1;
					q.push(v);
					maxDepth = max(maxDepth, distance[v]);
				}
			}
		}

		return maxDepth;
	}

	int qPow(int x, int y)
	{
		int result = 1;
		for (; y; y >>= 1)
		{
			if (y & 1)
			{
				result = 1ll * result * x % mod;
			}
			x = 1ll * x * x % mod;
		}

		return result;
	}
public:
	int assignEdgeWeights(vector<vector<int>>& edges)
	{
		n = edges.size() + 1;
		for (auto& edge : edges)
		{
			int u = edge[0];
			int v = edge[1];

			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		int maxDepth = this->bfs();
		int result = this->qPow(2, maxDepth - 1);

		return result;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> edges;
	int u, v;
	for (int i = 0; i < n; i++)
	{
		cin >> u >> v;
		edges.push_back({ u, v });
	}

	Solution sol;
	int result = sol.assignEdgeWeights(edges);
	cout << result << "\n";
	return 0;
}