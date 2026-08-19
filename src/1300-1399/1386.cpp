/*
Tags
level-medium
array, hash-table, greedy, bit-manipulation

Problem Description
1386. Cinema Seat Allocation

A cinema has n rows of seats, numbered from 1 to n. Each row has 10 seats, numbered from 1 to 10.
You are given a 2D integer array reservedSeats, where reservedSeats[i] = [rowi, seati] means that seat seati in row rowi is already reserved.
A four-person group must be assigned to four seats in the same row. The group can be seated in one of the following seat blocks:
seats 2, 3, 4, 5
seats 4, 5, 6, 7
seats 6, 7, 8, 9
A block can be used only if none of its seats are reserved. Each seat can be assigned to at most one group.
Return an integer denoting the maximum number of four-person groups that can be assigned.

Example 1:
Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
Output: 4
Explanation: The figure above shows an optimal allocation of four groups. Seats marked in blue are already reserved, and each set of four contiguous seats marked in orange is assigned to one group.

Example 2:
Input: n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
Output: 2

Example 3:
Input: n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
Output: 4

Constraints:
1 <= n <= 10^9
1 <= reservedSeats.length <= min(10 * n, 10^4)
reservedSeats[i] == [rowi, seati]
1 <= rowi <= n
1 <= seati <= 10
All reservedSeats[i] are distinct.
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
	int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {

		// when seats other than 1,2,3,4 are already reserved
		int left = 0b11110000;
		// when seats other than 4,5,6,7 are already reserved
		int middle = 0b11000011;
		// when seats other than 6,7,8,9 are already reserved
		int right = 0b00001111;

		// map(row, seat bitmask) to store the seat bitmask for a particular row
		unordered_map<int, int> occupied;
		for (const vector<int>& seat : reservedSeats)
		{
			if (seat[1] >= 2 && seat[1] <= 9)
			{
				occupied[seat[0]] |= (1 << (seat[1] - 2));
			}
		}

		// The map occupied stored the bitmasks for the rows where atleast a seat is already reserved.
		// So, n-occupied.size() number of rows are totally free to allocate, where we can allocate max 2 families.
		int result = (n - occupied.size()) * 2;

		// Rest we need to check if we can allocate any more families in the other rows, where already there are some reservations.
		for (auto& [row, bitmask] : occupied)
		{
			// Check if we can allocate seats in left or middle or right.
			if (((bitmask | left) == left) || ((bitmask | middle) == middle) || ((bitmask | right) == right))
			{
				// If yes, then increment the no of families by 1
				result += 1;
			}
		}

		return result;
	}
};

int main()
{
	int n, k;
	cin >> n >> k;
	vector<vector<int>> reservedSeats(k, vector<int>(2));
	for (int i = 0; i < k; i++)
	{
		cin >> reservedSeats[i][0] >> reservedSeats[i][1];
	}

	Solution sol;
	int result = sol.maxNumberOfFamilies(n, reservedSeats);
	cout << result << "\n";
	return 0;
}