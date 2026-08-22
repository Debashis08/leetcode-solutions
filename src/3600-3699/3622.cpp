/*
Tags
level-easy
math

Problem Description
3622. Check Divisibility by Digit Sum and Product

You are given a positive integer n. Determine whether n is divisible by the sum of the following two values:
The digit sum of n (the sum of its digits).
The digit product of n (the product of its digits).
Return true if n is divisible by this sum; otherwise, return false.

Example 1:
Input: n = 99
Output: true
Explanation:
Since 99 is divisible by the sum (9 + 9 = 18) plus product (9 * 9 = 81) of its digits (total 99), the output is true.

Example 2:
Input: n = 23
Output: false
Explanation:
Since 23 is not divisible by the sum (2 + 3 = 5) plus product (2 * 3 = 6) of its digits (total 11), the output is false.

Constraints:
1 <= n <= 10^6
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
    bool checkDivisibility(int n) {
        int sum = 0;
        int prod = 1;
        int m = n;
        while (n)
        {
            int rem = n % 10;
            sum += rem;
            prod *= rem;
            n /= 10;
        }

        return (m % (sum + prod) == 0);
    }
};

int main()
{
    int n;
    cin >> n;
    Solution sol;
    bool result = sol.checkDivisibility(n);
    cout << result << "\n";
	return 0;
}