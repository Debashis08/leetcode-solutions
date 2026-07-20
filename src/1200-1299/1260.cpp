/*
Tags
level-easy
array, matrix, simulation

Problem Description
1260. Shift 2D Grid

Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
In one shift operation:
Element at grid[i][j] moves to grid[i][j + 1].
Element at grid[i][n - 1] moves to grid[i + 1][0].
Element at grid[m - 1][n - 1] moves to grid[0][0].
Return the 2D grid after applying shift operation k times.

Example 1:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[9,1,2],[3,4,5],[6,7,8]]

Example 2:
Input: grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
Output: [[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

Example 3:
Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
Output: [[1,2,3],[4,5,6],[7,8,9]]

Constraints:
m == grid.length
n == grid[i].length
1 <= m <= 50
1 <= n <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100
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
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k)
    {
        if (!k)
        {
            return grid;
        }

        int rows = grid.size();
        int columns = grid[0].size();
        int n = rows * columns;
        k = k % n;
        if (!k)
        {
            return grid;
        }

        auto shift = [&](int i, int j)
            {
                while (i < j)
                {
                    swap(grid[i / columns][i % columns], grid[j / columns][j % columns]);
                    i++;
                    j--;
                }
            };

        shift(0, n - 1);
        shift(0, k - 1);
        shift(k, n - 1);

        return grid;
    }
};

int main()
{
    int rows, columns, k;
    cin >> rows >> columns >> k;
    vector<vector<int>> grid(rows, vector<int>(columns, 0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cin >> grid[i][j];
        }
    }

    Solution sol;
    vector<vector<int>> result = sol.shiftGrid(grid, k);
    Core::printTwoDimensionalVectorResult(result);
	return 0;
}