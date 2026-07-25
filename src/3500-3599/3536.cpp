/*
Tags
level-easy
math, sorting

Problem Description
3536. Maximum Product of Two Digits

You are given a positive integer n.
Return the maximum product of any two digits in n.
Note: You may use the same digit twice if it appears more than once in n.

Example 1:
Input: n = 31
Output: 3
Explanation:
The digits of n are [3, 1].
The possible products of any two digits are: 3 * 1 = 3.
The maximum product is 3.

Example 2:
Input: n = 22
Output: 4
Explanation:
The digits of n are [2, 2].
The possible products of any two digits are: 2 * 2 = 4.
The maximum product is 4.

Example 3:
Input: n = 124
Output: 8
Explanation:
The digits of n are [1, 2, 4].
The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8.
The maximum product is 8.

Constraints:
10 <= n <= 10^9
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
    int maxProduct(int n) {
        int largest = -1;
        int secondLargest = -1;

        while (n > 0)
        {
            int rem = n % 10;
            if (rem > largest)
            {
                secondLargest = largest;
                largest = rem;
            }
            else if (rem > secondLargest)
            {
                secondLargest = rem;
            }

            n /= 10;
        }

        return largest * secondLargest;
    }
};

int main()
{
    int n;
    cin >> n;
    Solution sol;
    int result = sol.maxProduct(n);
    cout << result << "\n";
	return 0;
}