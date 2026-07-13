/*
Tags
level-medium
enumeration

Problem Description
1291. Sequential Digits

An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

Example 1:
Input: low = 100, high = 300
Output: [123,234]

Example 2:
Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]

Constraints:
10 <= low <= high <= 10^9
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
private:
	vector<int> result;
	void addSequentialDigits(int current, int lastDigit, int low, int high)
	{
		if (current >= low && current <= high)
		{
			result.push_back(current);
		}
		if (current > high || lastDigit == 9)
		{
			return;
		}
		int next = current * 10 + (lastDigit + 1);
		this->addSequentialDigits(next, lastDigit + 1, low, high);
	}
public:
	vector<int> sequentialDigits(int low, int high)
	{
		for (int i = 1; i < 9; i++)
		{
			this->addSequentialDigits(i, i, low, high);
		}

		sort(result.begin(), result.end());
		return result;
	}
};

int main()
{
	int low, high;
	cin >> low >> high;
	Solution sol;
	vector<int> result = sol.sequentialDigits(low, high);
	Core::printVectorResult(result);
	return 0;
}