/*
Tags



Problem Description

You are given two 0-indexed integer permutations A and B of length n.
A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B.
Return the prefix common array of A and B.
A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly once.

Example 1:
Input: A = [1,3,2,4], B = [3,1,2,4]
Output: [0,2,3,4]
Explanation: At i = 0: no number is common, so C[0] = 0.
At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.

Example 2:
Input: A = [2,3,1], B = [3,1,2]
Output: [0,1,3]
Explanation: At i = 0: no number is common, so C[0] = 0.
At i = 1: only 3 is common in A and B, so C[1] = 1.
At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.


Constraints:
1 <= A.length == B.length == n <= 50
1 <= A[i], B[i] <= n
It is guaranteed that A and B are both a permutation of n integers.

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

const int MOD = 1e9 + 7;

// Fast I/O
void FastIO()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

class Solution
{
private:
	long long GCD(long long a, long long b)
	{
		while (b)
		{
			a %= b;
			swap(a, b);
		}
		return a;
	}

	long long LCM(long long a, long long b)
	{
		return a / this->GCD(a, b) * b;
	}

	long long Power(long long base, long long exp, long long mod = MOD)
	{
		long long result = 1;
		base %= mod;
		while (exp > 0)
		{
			if (exp & 1)
				result = result * base % mod;
			base = base * base % mod;
			exp >>= 1;
		}
		return result;
	}

public:
	vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
		int n = A.size();
		unordered_map<int, int> mp;
		vector<int> result(n, 0);
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			mp[A[i]]++;
			mp[B[i]]++;

			if (A[i] == B[i])
			{
				count++;
			}
			else if (mp[A[i]] == 2 && mp[B[i]] == 2)
			{
				count += 2;
			}
			else if (mp[A[i]] == 2 || mp[B[i]] == 2)
			{
				count++;
			}
			else
			{

			}
			result[i] = count;
		}

		return result;
	}
};

int main()
{
	FastIO();
	int n;
	int x;
	vector<int> vec1;
	vector<int> vec2;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		vec1.push_back(x);
	}

	for (int i = 0; i < n; i++)
	{
		cin >> x;
		vec2.push_back(x);
	}

	Solution solution;
	auto result = solution.findThePrefixCommonArray(vec1, vec2);
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << " ";
	}

	return 0;
}