/*
Tags

level-hard, array, dfs, dp

Problem Description

Given an array of integers arr and an integer d. In one step you can jump from index i to index:
i + x where: i + x < arr.length and  0 < x <= d.
i - x where: i - x >= 0 and  0 < x <= d.
In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).
You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.
Notice that you can not jump outside of the array at any time.

Example 1:
Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
Output: 4
Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.
Similarly You cannot jump from index 3 to index 2 or index 1.

Example 2:
Input: arr = [3,3,3,3,3], d = 3
Output: 1
Explanation: You can start at any index. You always cannot jump to any index.

Example 3:
Input: arr = [7,6,5,4,3,2,1], d = 1
Output: 7
Explanation: Start at index 0. You can visit all the indicies.


Constraints:
1 <= arr.length <= 1000
1 <= arr[i] <= 10^5
1 <= d <= arr.length

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
using namespace std;


class Solution {
private:
    vector<int> dp;
public:
    void dfs(vector<int>& arr, int id, int d, int n)
    {
        if (dp[id] != -1)
        {
            return;
        }
        dp[id] = 1;
        for (int i = id - 1; i >= 0 && id - i <= d && arr[id] > arr[i]; i--)
        {
            dfs(arr, i, d, n);
            dp[id] = max(dp[id], dp[i] + 1);
        }
        for (int i = id + 1; i<n && i - id <= d && arr[id]>arr[i]; i++)
        {
            dfs(arr, i, d, n);
            dp[id] = max(dp[id], dp[i] + 1);
        }
    }

    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        dp.resize(n, -1);
        for (int i = 0; i < n; i++)
        {
            dfs(arr, i, d, n);
        }
        return *max_element(dp.begin(), dp.end());
    }
};

int main()
{
    Solution sol;

    int d;
    int n;
    vector<int> vec;
    cin >> d >> n;
    int x;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        vec.push_back(x);
    }

    cout << sol.maxJumps(vec, d);

    return 0;
}