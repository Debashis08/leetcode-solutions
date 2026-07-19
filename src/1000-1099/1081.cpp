/*
Tags
level-medium
string, stack, greedy, monotonic-stack

Problem Description
1081. Smallest Subsequence of Distinct Characters

Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.
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
    string smallestSubsequence(string s)
    {
        vector<int> visited(26, 0), count(26, 0);
        for (char ch : s)
        {
            count[ch - 'a']++;
        }

        string result = "";
        for (char ch : s)
        {
            if (!visited[ch - 'a'])
            {
                while (!result.empty() && result.back() > ch)
                {
                    if (count[result.back() - 'a'] > 0)
                    {
                        visited[result.back() - 'a'] = 0;
                        result.pop_back();
                    }
                    else
                    {
                        break;
                    }
                }
                visited[ch - 'a'] = 1;
                result.push_back(ch);
            }
            count[ch - 'a'] -= 1;
        }

        return result;
    }
};

int main()
{
    string s;
    cin >> s;
    Solution sol;
    string result = sol.smallestSubsequence(s);
    cout << result << "\n";
	return 0;
}