/*
Tags
level-medium
array, math, greedy, minimax, counting, game-theory, nim-game, zero-sum-game

Problem Description
2029. Stone Game IX

Alice and Bob continue their games with stones. There is a row of n stones, and each stone has an associated value. You are given an integer array stones, where stones[i] is the value of the ith stone.
Alice and Bob take turns, with Alice starting first. On each turn, the player may remove any stone from stones. The player who removes a stone loses if the sum of the values of all removed stones is divisible by 3.
Bob will win automatically if there are no remaining stones (even if it is Alice's turn).
Assuming both players play optimally, return true if Alice wins and false if Bob wins.

Example 1:
Input: stones = [2,1]
Output: true
Explanation: The game will be played as follows:
- Turn 1: Alice can remove either stone.
- Turn 2: Bob removes the remaining stone.
The sum of the removed stones is 1 + 2 = 3 and is divisible by 3. Therefore, Bob loses and Alice wins the game.

Example 2:
Input: stones = [2]
Output: false
Explanation: Alice will remove the only stone, and the sum of the values on the removed stones is 2.
Since all the stones are removed and the sum of values is not divisible by 3, Bob wins the game.

Example 3:
Input: stones = [5,1,2,4,3]
Output: false
Explanation: Bob will always win. One possible way for Bob to win is shown below:
- Turn 1: Alice can remove the second stone with value 1. Sum of removed stones = 1.
- Turn 2: Bob removes the fifth stone with value 3. Sum of removed stones = 1 + 3 = 4.
- Turn 3: Alices removes the fourth stone with value 4. Sum of removed stones = 1 + 3 + 4 = 8.
- Turn 4: Bob removes the third stone with value 2. Sum of removed stones = 1 + 3 + 4 + 2 = 10.
- Turn 5: Alice removes the first stone with value 5. Sum of removed stones = 1 + 3 + 4 + 2 + 5 = 15.
Alice loses the game because the sum of the removed stones (15) is divisible by 3. Bob wins the game.

Constraints:
1 <= stones.length <= 10^5
1 <= stones[i] <= 10^4
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
    bool stoneGameIX(vector<int>& stones) {
        // Because the losing condition is strictly based on the sum of removed stones being divisible by 3, 
        // the actual integer values of the stones do not matter. The only thing that matters is their value modulo 3.

        // count[0] for %3==0, count[1] for %3==1, count[2] for %3==2
        int count[3] = { 0, 0, 0 };

        for (int stone : stones)
        {
            count[stone % 3]++;
        }

        // Because Type 0 stones only flip the turn, we can determine the winner purely based on whether the count of Type 0 stones is even or odd.

        // Condition 1: the count of Type 0 stones is even.
        // Alice wins as long as she has at least one Type 1 stone and at least one Type 2 stone.
        if (count[0] % 2 == 0)
        {
            return count[1] >= 1 && count[2] >= 1;
        }

        // Condition 2: The count of Type 0 stones is odd.
        // For Alice to overcome this turn-skip and win, there must be a severe imbalance between Type 1 and Type 2 stones.
        // Specifically, Alice only wins if the absolute difference between the count of Type 1 stones and Type 2 stones is strictly greater than 2.
        return abs(count[1] - count[2]) > 2;
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
    bool result = sol.stoneGameIX(stones);
    cout << result << "\n";
	return 0;
}