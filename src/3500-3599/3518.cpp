/*
Tags
level-hard
hash-table, math, string, combinatorics, counting

Problem Description
3518. Smallest Palindromic Rearrangement II

You are given a palindromic string s and an integer k.
Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.

Example 1:
Input: s = "abba", k = 2
Output: "baab"
Explanation:
The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".

Example 2:
Input: s = "aa", k = 2
Output: ""
Explanation:
There is only one palindromic rearrangement: "aa".
The output is an empty string since k = 2 exceeds the number of possible rearrangements.

Example 3:
Input: s = "bacab", k = 1
Output: "abcba"
Explanation:
The two distinct palindromic rearrangements of "bacab" are "abcba" and "bacab".
Lexicographically, "abcba" comes before "bacab". Since k = 1, the output is "abcba".

Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.
s is guaranteed to be palindromic.
1 <= k <= 10^6
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
    string smallestPalindrome(string s, int k) {
        // Step 1: Map frequencies and identify the palindrome structure
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> counts(26, 0);
        char oddChar = 0;
        for (int i = 0; i < 26; ++i) {
            counts[i] = freq[i] / 2;
            if (freq[i] % 2 != 0) {
                oddChar = i + 'a';
            }
        }

        // Ensure k is within the total possible distinct palindromes
        long long totalPerms = getPerms(counts, k);
        if (k > totalPerms) return "";

        // Step 2 & 3: Build the first half of the palindrome lexicographically
        string first_half = "";
        int m = s.length() / 2;

        for (int i = 0; i < m; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (counts[c] > 0) {
                    counts[c]--;
                    long long perms = getPerms(counts, k);

                    if (k <= perms) {
                        // The target permutation is in this branch
                        first_half += (char)(c + 'a');
                        break;
                    }
                    else {
                        // Skip this branch and adjust k
                        k -= perms;
                        counts[c]++;
                    }
                }
            }
        }

        // Step 4: Assemble the final palindromic string
        string res = first_half;
        if (oddChar != 0) res += oddChar;

        string rev_half = first_half;
        reverse(rev_half.begin(), rev_half.end());
        res += rev_half;

        return res;
    }

private:
    // Calculates the distinct permutations for a given set of character counts.
    // Caps early if the combinations exceed the provided cap to prevent overflow.
    long long getPerms(const vector<int>& counts, long long cap) {
        long long res = 1;
        int max_c = 0;
        int max_idx = -1;

        // Find the character with the maximum count to optimize calculation speed
        for (int i = 0; i < 26; ++i) {
            if (counts[i] > max_c) {
                max_c = counts[i];
                max_idx = i;
            }
        }

        if (max_idx == -1) return 1;

        int total = max_c;
        for (int i = 0; i < 26; ++i) {
            if (i == max_idx || counts[i] == 0) continue;

            // Multiply incrementally: exact formula evaluation without precision loss
            for (int j = 1; j <= counts[i]; ++j) {
                total++;
                res = res * total / j;
                if (res > cap) return cap + 1; // Early exit pruning 
            }
        }

        return res;
    }
};

int main()
{
    string s;
    int k;
    cin >> s;
    cin >> k;
    Solution sol;
    string result = sol.smallestPalindrome(s, k);
    cout << result << "\n";
	return 0;
}