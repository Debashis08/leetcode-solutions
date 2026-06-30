/*
Tags
level-easy
hash-table, string, counting

Problem Description
1189. Maximum Number of Balloons
Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.
You can use each character in text at most once. Return the maximum number of instances that can be formed.

Example 1:
Input: text = "nlaebolko"
Output: 1

Example 2:
Input: text = "loonbalxballpoon"
Output: 2

Example 3:
Input: text = "leetcode"
Output: 0

Constraints:
1 <= text.length <= 10^4
text consists of lower case English letters only.
Note: This question is the same as 2287: Rearrange Characters to Make Target String.

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
	int maxNumberOfBalloons(string text)
	{
		vector<int> freq(5, 0);
		string s = "balon";
		for (auto& ch : text)
		{
			for (int i = 0; i < 5; i++)
			{
				if (ch == s[i])
				{
					freq[i]++;
				}
			}
		}

		return min({ freq[0], freq[1],freq[2] >> 1,freq[3] >> 1,freq[4] });
	}
};

int main()
{
	string text;
	cin >> text;
	Solution sol;
	int result = sol.maxNumberOfBalloons(text);
	cout << result << "\n";

	return 0;
}