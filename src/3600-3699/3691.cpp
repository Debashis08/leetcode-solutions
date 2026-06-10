/*
Tags
level-hard
array, greedy, heap, priority-queue, segment-tree


Problem Description
3691. Maximum Total Subarray Value II
You are given an integer array nums of length n and an integer k.
You must select exactly k distinct subarrays nums[l..r] of nums. Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.
The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).
The total value is the sum of the values of all chosen subarrays.
Return the maximum possible total value you can achieve.

Example 1:
Input: nums = [1,3,2], k = 2
Output: 4
Explanation:
One optimal approach is:
Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Example 2:
Input: nums = [4,2,5,1], k = 3
Output: 12
Explanation:
One optimal approach is:
Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.



Constraints:

1 <= n == nums.length <= 5 * 10​​​​​​​^4
0 <= nums[i] <= 10^9
1 <= k <= min(10^5, n * (n + 1) / 2)

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

class SegmentTree
{
private:
    int n;
    vector<int> maxv, minv;
public:
    SegmentTree(vector<int>& nums)
    {
        n = nums.size();
        maxv.resize(n * 4);
        minv.resize(n * 4);
        this->build(1, 0, n - 1, nums);
    }

    void build(int node, int l, int r, vector<int>& nums)
    {
        if (l == r)
        {
            maxv[node] = minv[node] = nums[l];
            return;
        }
        int m = (l + r) / 2;
        build(node * 2, l, m, nums);
        build(node * 2 + 1, m + 1, r, nums);
        maxv[node] = max(maxv[node * 2], maxv[node * 2 + 1]);
        minv[node] = min(minv[node * 2], minv[node * 2 + 1]);
    }
    int query_max(int node, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return maxv[node];
        }
        int m = (l + r) / 2;
        int res = INT_MIN;
        if (ql <= m)
        {
            res = max(res, query_max(node * 2, l, m, ql, qr));
        }
        if (qr > m)
        {
            res = max(res, query_max(node * 2 + 1, m + 1, r, ql, qr));
        }

        return res;
    }

    int query_min(int node, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return minv[node];
        }
        int m = (l + r) / 2;
        int res = INT_MAX;
        if (ql <= m)
        {
            res = min(res, query_min(node * 2, l, m, ql, qr));
        }
        if (qr > m)
        {
            res = min(res, query_min(node * 2 + 1, m + 1, r, ql, qr));
        }
        return res;
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k)
    {
        int n = nums.size();
        SegmentTree seg(nums);
        priority_queue<tuple<int, int, int>> pq;
        for (int l = 0; l < n; l++)
        {
            pq.emplace(seg.query_max(1, 0, n - 1, l, n - 1) - seg.query_min(1, 0, n - 1, l, n - 1), l, n - 1);
        }

        long long res = 0;
        while (k--)
        {
            auto [val, l, r] = pq.top();
            pq.pop();
            res += val;
            if (r > l)
            {
                pq.emplace(seg.query_max(1, 0, n - 1, l, r - 1) - seg.query_min(1, 0, n - 1, l, r - 1), l, r - 1);
            }
        }

        return res;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    Solution sol;
    long long result = sol.maxTotalValue(nums, k);
    cout << result << "\n";
	return 0;
}