/*
Tags
level-medium
dp, digit-dp, math


Problem Description
3751. Total Waviness of Numbers in Range I
You are given two integers num1 and num2 representing an inclusive range [num1, num2].
The waviness of a number is defined as the total count of its peaks and valleys:
A digit is a peak if it is strictly greater than both of its immediate neighbors.
A digit is a valley if it is strictly less than both of its immediate neighbors.
The first and last digits of a number cannot be peaks or valleys.
Any number with fewer than 3 digits has a waviness of 0.
Return the total sum of waviness for all numbers in the range [num1, num2].

Example 1:
Input: num1 = 120, num2 = 130
Output: 3
Explanation:
In the range [120, 130]:
120: middle digit 2 is a peak, waviness = 1.
121: middle digit 2 is a peak, waviness = 1.
130: middle digit 3 is a peak, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 2:
Input: num1 = 198, num2 = 202
Output: 3
Explanation:
In the range [198, 202]:
198: middle digit 9 is a peak, waviness = 1.
201: middle digit 0 is a valley, waviness = 1.
202: middle digit 0 is a valley, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 3:
Input: num1 = 4848, num2 = 4848
Output: 2
Explanation:
Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

Constraints:
1 <= num1 <= num2 <= 10^5
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

using ll = long long;
class Solution {
private:
	ll memoCount[16][10][10];
	ll memoSum[16][10][10];
	string s;
public:
	pair<ll, ll> dfs(int pos, int prev, int cur, bool isLimit, bool isLeading)
	{
		if (pos == s.length())
		{
			return { 1,0 };
		}

		if (!isLimit && !isLeading && prev >= 0 && cur >= 0)
		{
			if (memoCount[pos][prev][cur] != -1)
			{
				return { memoCount[pos][prev][cur], memoSum[pos][prev][cur] };
			}
		}

		ll count = 0;
		ll sum = 0;
		int limitDigit = isLimit ? (s[pos] - '0') : 9;
		for (int digit = 0; digit <= limitDigit; digit++)
		{
			bool nextLeading = isLeading && (digit == 0);
			int nextPrev = cur;
			int nextCur = nextLeading ? -1 : digit;
			bool nextLimit = isLimit && (digit == limitDigit);

			pair<ll, ll>result = this->dfs(pos + 1, nextPrev, nextCur, nextLimit, nextLeading);
			ll subCount = result.first;
			ll subSum = result.second;

			if (!nextLeading && prev >= 0 && cur >= 0)
			{
				bool isPeak = (prev<cur && cur>digit);
				bool isTrough = (prev > cur && cur < digit);

				if (isPeak || isTrough)
				{
					sum += subCount;
				}
			}

			count += subCount;
			sum += subSum;
		}

		if (!isLimit && !isLeading && prev >= 0 && cur >= 0)
		{
			memoCount[pos][prev][cur] = count;
			memoSum[pos][prev][cur] = sum;
		}

		return { count, sum };
	}
	ll solve(int num)
	{
		if (num < 100)
		{
			return 0;
		}
		s = to_string(num);
		memset(memoCount, -1, sizeof(memoCount));
		memset(memoSum, -1, sizeof(memoSum));
		pair<ll, ll> result = this->dfs(0, -1, -1, true, true);
		return result.second;
	}
	int totalWaviness(int num1, int num2) {
		return (int)(this->solve(num2) - this->solve(num1 - 1));
	}
};

int main()
{
	int num1, num2;
	cin >> num1 >> num2;
	Solution sol;
	int result = sol.totalWaviness(num1, num2);
	cout << result << "\n";
	return 0;
}