/*
Tags
level-medium
array, bfs, graph, heap, matrix, shortest-path

Problem Description
3286. Find a Safe Walk Through a Grid

You are given an m x n binary matrix grid and an integer health.
You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).
You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.
Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.
Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.

Example 1:
Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.

Example 2:
Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3
Output: false
Explanation:
A minimum of 4 health points is needed to reach the final cell safely.

Example 3:
Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5
Output: true
Explanation:
The final cell can be reached safely by walking along the gray cells below.
Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 50
2 <= m * n
1 <= health <= m + n
grid[i][j] is either 0 or 1.
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
    bool findSafeWalkImplementation01(vector<vector<int>>& grid, int health)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> distance(m, vector<int>(n, -1));
        vector<vector<int>> directions = { {0, -1},{0, 1},{1, 0},{-1, 0} };

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        pq.emplace(grid[0][0], 0, 0);

        while (!pq.empty())
        {
            auto [val, di, dj] = pq.top();
            pq.pop();
            if (distance[di][dj] >= 0)
            {
                continue;
            }
            distance[di][dj] = val;
            for (auto& dir : directions)
            {
                int dx = di + dir[0];
                int dy = dj + dir[1];
                if (dx < 0 || dy < 0 || dx >= m || dy >= n || distance[dx][dy] >= 0)
                {
                    continue;
                }
                pq.emplace(val + grid[dx][dy], dx, dy);
            }
        }

        return distance[m - 1][n - 1] < health;
    }

    bool findSafeWalkImplementation02(vector<vector<int>>& grid, int health)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> distance(m, vector<int>(n, INT_MAX));
        vector<vector<int>> directions = { {0, -1},{0, 1},{1, 0},{-1, 0} };

        deque<pair<int, int>> q;
        q.emplace_front(0, 0);
        distance[0][0] = grid[0][0];
        while (!q.empty())
        {
            auto [di, dj] = q.front();
            q.pop_front();
            if (di == m - 1 && dj == n - 1)
            {
                return true;
            }

            for (auto& dir : directions)
            {
                int dx = di + dir[0];
                int dy = dj + dir[1];
                if (dx < 0 || dy < 0 || dx >= m || dy >= n)
                {
                    continue;
                }
                int cost = distance[di][dj] + grid[dx][dy];
                if (cost >= health)
                {
                    continue;
                }
                if (cost < distance[dx][dy])
                {
                    distance[dx][dy] = cost;
                    if (grid[dx][dy] == 0)
                    {
                        q.emplace_front(dx, dy);
                    }
                    else
                    {
                        q.emplace_back(dx, dy);
                    }
                }
            }
        }

        return false;
    }
};

int main()
{
    int m, n, health;
    cin >> m >> n >> health;
    vector<vector<int>> grid(m, vector<int>(n, -1));
    Solution sol;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
        }
    }
    //bool result = sol.findSafeWalkImplementation01(grid, health);
    bool result = sol.findSafeWalkImplementation02(grid, health);
    cout << result << "\n";
	return 0;
}