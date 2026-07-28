/*
Tags
level-medium
string, sorting, counting-sort

Problem Description
3517. Smallest Palindromic Rearrangement I

You are given a palindromic string s.
Return the lexicographically smallest palindromic permutation of s.

Example 1:
Input: s = "z"
Output: "z"
Explanation:
A string of only one character is already the lexicographically smallest palindrome.

Example 2:
Input: s = "babab"
Output: "abbba"
Explanation:
Rearranging "babab" → "abbba" gives the smallest lexicographic palindrome.

Example 3:
Input: s = "daccad"
Output: "acddca"
Explanation:
Rearranging "daccad" → "acddca" gives the smallest lexicographic palindrome.

Constraints:
1 <= s.length <= 10^5
s consists of lowercase English letters.
s is guaranteed to be palindromic.
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
    string smallestPalindrome(string s) {
        int len = s.length();
        int mid = len >> 1;
        sort(s.begin(), s.begin() + mid);

        for (int i = 0; i < mid; i++)
        {
            s[len - 1 - i] = s[i];
        }

        return s;
    }
};

int main()
{
    string s;
    cin >> s;
    Solution sol;
    string result = sol.smallestPalindrome(s);
    cout << result << "\n";
	return 0;
}