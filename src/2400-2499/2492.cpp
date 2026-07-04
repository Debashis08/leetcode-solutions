/*
Tags
level-medium
graph, dfs, bfs, union-find

Problem Description
2492. Minimum Score of a Path Between Two Cities

You are given a positive integer n representing n cities numbered from 1 to n.
You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei.
The cities graph is not necessarily connected.
The score of a path between two cities is defined as the minimum distance of a road in this path.
Return the minimum possible score of a path between cities 1 and n.
Note:
A path is a sequence of roads between two cities.
It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
The test cases are generated such that there is at least one path between 1 and n.

Example 1:
Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
Output: 5
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
It can be shown that no other path has less score.

Example 2:
Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
Output: 2
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4. The score of this path is min(2,2,4,7) = 2.

Constraints:
2 <= n <= 10^5
1 <= roads.length <= 10^5
roads[i].length == 3
1 <= ai, bi <= n
ai != bi
1 <= distancei <= 10^4
There are no repeated edges.
There is at least one path between 1 and n.
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
    int minScore(int n, vector<vector<int>>& roads)
    {
        // graph[u]=[[v,w],...]
        vector<vector<pair<int, int>>> graph(n + 1);

        for (auto& it : roads)
        {
            graph[it[0]].push_back({ it[1],it[2] });
            graph[it[1]].push_back({ it[0],it[2] });
        }

        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(1);
        visited[1] = true;
        int result = INT_MAX;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (auto& [v, w] : graph[u])
            {
                result = min(result, w);
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        return result;
    }
};

int main()
{
    int n, m;
    Solution sol;
    cin >> n >> m;
    vector<vector<int>> roads(m, vector<int>(3, -1));
    for (int i = 0; i < m; i++)
    {
        cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
    }
    int result = sol.minScore(n, roads);
    cout << result << "\n";
	return 0;
}