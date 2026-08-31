/*
Tags
level-medium
dfs, bfs, graph

Problem Description
3310. Remove Methods From Project

You are maintaining a project that has n methods numbered from 0 to n - 1.
You are given two integers n and k, and a 2D integer array invocations, where invocations[i] = [ai, bi] indicates that method ai invokes method bi.
There is a known bug in method k. Method k, along with any method invoked by it, either directly or indirectly, are considered suspicious and we aim to remove them.
A group of methods can only be removed if no method outside the group invokes any methods within it.
Return an array containing all the remaining methods after removing all the suspicious methods. You may return the answer in any order. 
If it is not possible to remove all the suspicious methods, none should be removed.

Example 1:
Input: n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
Output: [0,1,2,3]
Explanation:
Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.

Example 2:
Input: n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
Output: [3,4]
Explanation:
Methods 0, 1, and 2 are suspicious and they are not directly invoked by any other method. We can remove them.

Example 3:
Input: n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
Output: []
Explanation:
All methods are suspicious. We can remove them.

Constraints:
1 <= n <= 10^5
0 <= k <= n - 1
0 <= invocations.length <= 2 * 10^5
invocations[i] == [ai, bi]
0 <= ai, bi <= n - 1
ai != bi
invocations[i] != invocations[j]
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
#include "../core/core.h"
using namespace std;

constexpr int MAXN = 100005;
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        // Approach: Use BFS to check what are the methods/nodes which can be reached starting from the node k.
        // These are the nodes which all comes under the suspicious list.
        // Now need to check if there are any clean methods which calls any of these method from this suspicious list or not.
        // If yes, then we can not remove all the suspicious method, if not yes can remove all the suspicious method.

        // Graph of the nodes.
        vector<vector<int>> graph(n);

        // Store the in-degrees to know if a method is in suspicious list and it is being called by another clean method or not.
        vector<int> inDegree(n, 0);

        // Using bitset to know which methods are suspicious.
        bitset<MAXN> suspicious;

        // Create the graph.
        for (auto& it : invocations)
        {
            graph[it[0]].push_back(it[1]);
            inDegree[it[1]]++;
        }

        // Standard BFS run.
        queue<int> q;
        q.push(k);
        // Set the bit k as true as the method k has known bug.
        suspicious.set(k);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : graph[u])
            {
                // During the BFS run, decrease the indegree of the nodes which can be reached starting from node k.
                inDegree[v]--;
                if (!suspicious.test(v))
                {
                    q.push(v);
                    // Add in the suspicious list.
                    suspicious.set(v);
                }
            }
        }

        // Now we need to check if we can remove all the suspicious methods or we have dependency on them from other clean methods.
        bool canRemoveAll = true;
        vector<int> remaining;
        for (int i = -0; i < n; i++)
        {
            // Check if the current method is suspicious but it has in-degree > 0 which means,
            // there is atleat a clean method which calls this method, so there is dependency on node i.
            if (suspicious.test(i) && inDegree[i] > 0)
            {
                canRemoveAll = false;
                break;
            }
            else if (!suspicious.test(i))
            {
                remaining.push_back(i);
            }
        }

        // Check if canRemoveAll is false then we return all the nodes, without removing anything.
        if (!canRemoveAll)
        {
            vector<int> allNodes(n);
            iota(allNodes.begin(), allNodes.end(), 0);
            return allNodes;
        }

        // Else we remove the suspicious methods and return the remaining methods only.
        return remaining;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> invocations(n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        cin >> invocations[i][0] >> invocations[i][1];
    }

    Solution sol;
    vector<int> result = sol.remainingMethods(n, k, invocations);
    Core::printVectorResult(result);
	return 0;
}