/*
Tags
level-medium
string, enumeration

Problem Description
3499. Maximize Active Section with Trade I

You are given a binary string s of length n, where:
'1' represents an active section.
'0' represents an inactive section.
You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
Return the maximum number of active sections in s after making the optimal trade.
Note: Treat s as if it is augmented with a '1' at both ends, forming t = '1' + s + '1'. The augmented '1's do not contribute to the final count.

Example 1:
Input: s = "01"
Output: 1
Explanation:
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.

Example 2:
Input: s = "0100"
Output: 4
Explanation:
String "0100" → Augmented to "101001".
Choose "0100", convert "101001" → "100001" → "111111".
The final string without augmentation is "1111". The maximum number of active sections is 4.

Example 3:
Input: s = "1000100"
Output: 7
Explanation:
String "1000100" → Augmented to "110001001".
Choose "000100", convert "110001001" → "110000001" → "111111111".
The final string without augmentation is "1111111". The maximum number of active sections is 7.

Example 4:
Input: s = "01010"
Output: 4
Explanation:
String "01010" → Augmented to "1010101".
Choose "010", convert "1010101" → "1000101" → "1111101".
The final string without augmentation is "11110". The maximum number of active sections is 4.

Constraints:
1 <= n == s.length <= 10^5
s[i] is either '0' or '1'
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
    int maxActiveSectionsAfterTrade(string s)
    {
        int n = s.size();
        int count1 = count(s.begin(), s.end(), '1');

        int i = 0;
        int prev = INT_MIN;
        int curr = 0;
        int bestGain = 0;
        while (i < n)
        {
            int start = i;
            while (i < n && s[i] == s[start])
            {
                i++;
            }
            if (s[start] == '0')
            {
                curr = i - start;
                bestGain = max(bestGain, prev + curr);
                prev = curr;
            }
        }

        return count1 + bestGain;
    }
};

int main()
{
    string s;
    cin >> s;
    Solution sol;
    int result = sol.maxActiveSectionsAfterTrade(s);
    cout << result << "\n";
	return 0;
}