/*
Tags
level-easy
math, enumeration

Problem Description
3345. Smallest Divisible Digit Product I

You are given two integers n and t. Return the smallest number greater than or equal to n such that the product of its digits is divisible by t.

Example 1:
Input: n = 10, t = 2
Output: 10
Explanation:
The digit product of 10 is 0, which is divisible by 2, making it the smallest number greater than or equal to 10 that satisfies the condition.

Example 2:
Input: n = 15, t = 3
Output: 16
Explanation:
The digit product of 16 is 6, which is divisible by 3, making it the smallest number greater than or equal to 15 that satisfies the condition.

Constraints:
1 <= n <= 100
1 <= t <= 10
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
#include <bitset>
#include "../core/core.h"
using namespace std;

class Solution {
public:
    bool checkNumber(int num, int t)
    {
        int product = 1;
        while (num)
        {
            product *= (num % 10);
            num /= 10;
            if (product == 0)
            {
                break;
            }
        }
        return product % t == 0;
    }
    int smallestNumber(int n, int t) {
        while (!checkNumber(n, t))
        {
            n++;
        }
        return n;
    }
};

int main()
{
    int n, t;
    cin >> n >> t;
    Solution sol;
    int result = sol.smallestNumber(n, t);
    cout << result << "\n";
	return 0;
}