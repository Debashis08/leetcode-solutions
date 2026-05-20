/*
Tags



----------------------------------------------------------------------------------------------------------------------------

Problem Description



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