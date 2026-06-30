/*
Tags

level-easy, set, string

Problem Description
Count the Number of Special Characters I

You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
Return the number of special letters in word.

Example 1:
Input: word = "aaAbcBC"
Output: 3
Explanation:
The special characters in word are 'a', 'b', and 'c'.

Example 2:
Input: word = "abc"
Output: 0
Explanation:
No character in word appears in uppercase.

Example 3:
Input: word = "abBCab"
Output: 1
Explanation:
The only special character in word is 'b'.

Constraints:
1 <= word.length <= 50
word consists of only lowercase and uppercase English letters.

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


class Solution
{
public:
	int numberOfSpecialChars(string word)
	{
		unordered_set<char> s(word.begin(), word.end());
		int count = 0;
		for (char c = 'a'; c <= 'z'; c++)
		{
			if (s.count(c) && s.count(c - 'a' + 'A'))
			{
				count++;
			}
		}

		return count;
	}
};

int main()
{
	string word;
	cin >> word;
	Solution sol;
	cout << sol.numberOfSpecialChars(word);

	return 0;
}