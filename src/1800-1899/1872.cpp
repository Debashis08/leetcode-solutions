/*
Tags
level-hard
array, math, dp, minimax, prefix-sum, game-theory, zero-sum-game

Problem Description
1872. Stone Game VIII

Alice and Bob take turns playing a game, with Alice starting first.
There are n stones arranged in a row. On each player's turn, while the number of stones is more than one, they will do the following:
Choose an integer x > 1, and remove the leftmost x stones from the row.
Add the sum of the removed stones' values to the player's score.
Place a new stone, whose value is equal to that sum, on the left side of the row.
The game stops when only one stone is left in the row.
The score difference between Alice and Bob is (Alice's score - Bob's score). Alice's goal is to maximize the score difference, and Bob's goal is the minimize the score difference.
Given an integer array stones of length n where stones[i] represents the value of the ith stone from the left, return the score difference between Alice and Bob if they both play optimally.

Example 1:
Input: stones = [-1,2,-3,4,-5]
Output: 5
Explanation:
- Alice removes the first 4 stones, adds (-1) + 2 + (-3) + 4 = 2 to her score, and places a stone of
  value 2 on the left. stones = [2,-5].
- Bob removes the first 2 stones, adds 2 + (-5) = -3 to his score, and places a stone of value -3 on
  the left. stones = [-3].
The difference between their scores is 2 - (-3) = 5.

Example 2:
Input: stones = [7,-6,5,10,5,-2,-6]
Output: 13
Explanation:
- Alice removes all stones, adds 7 + (-6) + 5 + 10 + 5 + (-2) + (-6) = 13 to her score, and places a
  stone of value 13 on the left. stones = [13].
The difference between their scores is 13 - 0 = 13.

Example 3:
Input: stones = [-10,-12]
Output: -22
Explanation:
- Alice can only make one move, which is to remove both stones. She adds (-10) + (-12) = -22 to her
  score and places a stone of value -22 on the left. stones = [-22].
The difference between their scores is (-22) - 0 = -22.

Constraints:
n == stones.length
2 <= n <= 10^5
-10^4 <= stones[i] <= 10^4
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
    int stoneGameVIII(vector<int>& stones) {
        // Need to calculate the following
        // dp[i]=max(Alice's score - Bob's score
        // upto ith stone taken by Alice taking first turn).
        int n = stones.size();
        vector<int> pre;
        // Calculate the prefix sum starting from last,
        // as stone with same amount of sum is placed at the left, after removal of i stones.
        partial_sum(stones.begin(), stones.end(), back_inserter(pre));

        vector<int> f(n);

        // Base case, when only one stone is left, game stops.
        f[n - 1] = pre[n - 1];
        for (int i = n - 2; i >= 1; i--)
        {
            // The score difference can be calcualted as there are 2 possibilities,
            // 1. The current player does not choose i -> f[i]=f[i+1]
            // 2. The currnet player chooses i -> f[i]=pre[i]-f[i+1]
            f[i] = max(f[i + 1], pre[i] - f[i + 1]);
        }

        // Return f[1], as Alice can not choose only index 0 in her first move.
        return f[1];
    }
};

int main()
{
    int n;
    cin >> n;
    vector<int> stones(n);
    for (int i = 0; i < n; i++)
    {
        cin >> stones[i];
    }

    Solution sol;
    int result = sol.stoneGameVIII(stones);
    cout << result << "\n";
	return 0;
}