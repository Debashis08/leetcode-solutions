/*
Tags
level-medium
math

Problem Description
1344. Angle Between Hands of a Clock
Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.
Answers within 10-5 of the actual value will be accepted as correct.

Example 1:
Input: hour = 12, minutes = 30
Output: 165

Example 2:
Input: hour = 3, minutes = 30
Output: 75

Example 3:
Input: hour = 3, minutes = 15
Output: 7.5

Constraints:
1 <= hour <= 12
0 <= minutes <= 59

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
#include "../../core/core.h"
using namespace std;

class Solution
{
public:
    double angleClock(int hour, int minutes)
    {
        double minuteAngle = 6.0 * minutes;
        double hourAngle = 30.0 * (hour % 12) + 0.5 * minutes;

        double diff = abs(minuteAngle - hourAngle);
        return min(diff, 360.0 - diff);
    }
};

int main()
{
    int hour, minutes;
    cin >> hour >> minutes;
    Solution sol;
    double result = sol.angleClock(hour, minutes);
    cout << fixed << setprecision(5) << result << "\n";
	return 0;
}