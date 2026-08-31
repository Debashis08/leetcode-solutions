/*
Tags
level-hard
array, math, dp, game-theory
need-to-revisit

Problem Description
1563. Stone Game V

There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. 
Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, 
Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.
The game ends when there is only one stone remaining. Alice's score is initially zero.
Return the maximum score that Alice can obtain.

Example 1:
Input: stoneValue = [6,2,3,4,5,5]
Output: 18
Explanation: In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.

Example 2:
Input: stoneValue = [7,7,7,7,7,7,7]
Output: 28

Example 3:
Input: stoneValue = [4]
Output: 0

Constraints:
1 <= stoneValue.length <= 500
1 <= stoneValue[i] <= 10^6
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

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        // Number of stones
        int n = stoneValue.size();

        // Base case
        if (n <= 1)
        {
            return 0;
        }

        // Prefix sum for O(1) range sums.
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++)
        {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        // dp[i][j] stores the max score for subarray [i...j]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // maxL[i][j] = max_{k=i...j} (sum(i, k)+dp[i][k])
        vector<vector<int>> maxL(n, vector<int>(n, 0));

        // maxR[i][j] = max_{k=i...j} (sum(K, j)+dp[k][j])
        vector<vector<int>> maxR(n, vector<int>(n, 0));

        // Base case length 1 subarrays
        for (int i = 0; i < n; i++)
        {
            // dp[i][i] = 0, so it is just the stone values
            maxL[i][i] = stoneValue[i];
            maxR[i][i] = stoneValue[i];
        }

        // Iterate from bottom up
        for (int i = n - 1; i >= 0; i--)
        {
            // Monotonic split pointer
            int m = i - 1;
            for (int j = i + 1; j < n; j++)
            {
                int total = prefix[j + 1] - prefix[i];

                // Advance m as long as left_sum <= right_sum
                // (which is mathematically equivalent to left_sum * 2 <= total)
                while (m + 1 < j && (prefix[m + 2] - prefix[i]) * 2 <= total)
                {
                    m++;
                }

                int res = 0;

                // For k<=m, left_sum <= right_sum, Bob discards the right side
                if (m >= i)
                {
                    res = max(res, maxL[i][m]);
                }

                // Spcecial case check: if left_sum == right_sum, at point m
                bool isEqual = (m >= i && (prefix[m + 1] - prefix[i]) * 2 == total);
                if (isEqual)
                {
                    // Alice can choose, so we can check if the right side starting exactly at m+1
                    res = max(res, maxR[m + 1][j]);
                }
                else
                {
                    // Otherwise, for all k > m, left_sum > right_sum. Bob discards the left_side
                    // The right side evaluation begins at m+2
                    if (m + 2 <= j)
                    {
                        res = max(res, maxR[m + 2][j]);
                    }
                }
                dp[i][j] = res;

                // Update the running maximums for larger subarray calcaulations
                maxL[i][j] = max(maxL[i][j - 1], total + dp[i][j]);
                maxR[i][j] = max(maxR[i + 1][j], total + dp[i][j]);
            }
        }

        return dp[0][n - 1];
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> stoneValue(n);
    for (int i = 0; i < n; i++)
    {
        cin >> stoneValue[i];
    }
    Solution sol;
    int result = sol.stoneGameV(stoneValue);
    cout << result << "\n";
	return 0;
}