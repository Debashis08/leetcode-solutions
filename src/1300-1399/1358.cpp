/*
Tags
level-medium
hash-table, string, sliding-window

Problem Description
1358. Number of Substrings Containing All Three Characters

Given a string s consisting only of characters a, b and c.
Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Example 1:
Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

Example 2:
Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb".

Example 3:
Input: s = "abc"
Output: 1

Constraints:
3 <= s.length <= 5 x 10^4
s only consists of a, b or c characters.

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
    bool hasAllChars(vector<int>& freq)
    {
        return (freq[0] > 0 && freq[1] > 0 && freq[2] > 0);
    }

    int numberOfSubstringsImplementation01(string s)
    {
        int n = s.length();
        int left = 0;
        int right = 0;
        vector<int> freq(3, 0);
        int count = 0;
        while (right < n)
        {
            char ch = s[right];
            freq[ch - 'a']++;

            while (this->hasAllChars(freq))
            {
                count += n - right;
                char leftIndexChar = s[left];
                freq[leftIndexChar - 'a']--;
                left++;
            }
            right++;
        }

        return count;
    }

    int numberOfSubstringsImplementation02(string s)
    {
        int n = s.length();
        vector<int> lastPosition = { -1,-1,-1 };
        int count = 0;
        for (int pos = 0; pos < n; pos++)
        {
            lastPosition[s[pos] - 'a'] = pos;
            count += 1 + min({ lastPosition[0], lastPosition[1], lastPosition[2] });
        }

        return count;
    }
};

int main()
{
    string s;
    Solution sol;
    cin >> s;
    int result = sol.numberOfSubstringsImplementation01(s);
    //int result = sol.numberOfSubstringsImplementation02(s);
    cout << result << "\n";
	return 0;
}