/*
Tags
level-hard
array, math, dp, minimax, game-theory, zero-sum-game

Problem Description
1406. Stone Game III

Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array stoneValue.
Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2, or 3 stones from the first remaining stones in the row.
The score of each player is the sum of the values of the stones taken. The score of each player is 0 initially.
The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The game continues until all the stones have been taken.
Assume Alice and Bob play optimally.
Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with the same score.

Example 1:
Input: stoneValue = [1,2,3,7]
Output: "Bob"
Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6. Now the score of Bob is 7 and Bob wins.

Example 2:
Input: stoneValue = [1,2,3,-9]
Output: "Alice"
Explanation: Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5. In the next move, Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3. In the next move, Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.

Example 3:
Input: stoneValue = [1,2,3,6]
Output: "Tie"
Explanation: Alice cannot win this game. She can end the game in a draw if she decided to choose all the first three piles, otherwise she will lose.


Constraints:
1 <= stoneValue.length <= 5 * 10^4
-1000 <= stoneValue[i] <= 1000
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

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<long long> dp(n + 1, LLONG_MIN);
        // The Strategy
        // Let's define a state dp[i] as the maximum score difference the current player can achieve if the game starts at index i and continues to the end of the array.If the current player is at index i, 
        // they have up to 3 choices:
        // Take 1 stone: 
        // They gain stoneValue[i]. The opponent will then play optimally starting from i+1, achieving a score difference of dp[i+1]. Therefore, the current player's net score difference is stoneValue[i] - dp[i+1].
        // Take 2 stones: 
        // They gain stoneValue[i] + stoneValue[i+1]. Their net score difference becomes (stoneValue[i] + stoneValue[i+1]) - dp[i+2].
        // Take 3 stones: 
        // They gain stoneValue[i] + stoneValue[i+1] + stoneValue[i+2]. Their net score difference becomes (stoneValue[i] + stoneValue[i+1] + stoneValue[i+2]) - dp[i+3].
        // The current player will choose the option that yields the highest net score difference:dp[i] = max({Option 1, Option 2, Option 3})
        // We evaluate this from right to left (from the end of the array to the beginning) because the decision at index i depends on the outcomes of future states.
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            int currentTake = 0;
            for (int j = 0; j < 3 && (i + j) < n; j++)
            {
                currentTake += stoneValue[i + j];
                dp[i] = max(dp[i], currentTake - dp[i + j + 1]);
            }
        }
        return (dp[0] > 0 ? "Alice" : (dp[0] < 0 ? "Bob" : "Tie"));
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
    string result = sol.stoneGameIII(stoneValue);
    cout << result << "\n";
	return 0;
}