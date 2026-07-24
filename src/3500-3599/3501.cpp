/*
Tags
level-hard
array, string, binary-search, segment-tree

Problem Description
3501. Maximize Active Section with Trade II

You are given a binary string s of length n, where:
'1' represents an active section.
'0' represents an inactive section.
You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
Additionally, you are given a 2D array queries, where queries[i] = [li, ri] represents a substring s[li...ri].
For each query, determine the maximum possible number of active sections in s after making the optimal trade on the substring s[li...ri].
Return an array answer, where answer[i] is the result for queries[i].

Note
For each query, treat s[li...ri] as if it is augmented with a '1' at both ends, forming t = '1' + s[li...ri] + '1'. The augmented '1's do not contribute to the final count.
The queries are independent of each other.

Example 1:
Input: s = "01", queries = [[0,1]]
Output: [1]
Explanation:
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.

Example 2:
Input: s = "0100", queries = [[0,3],[0,2],[1,3],[2,3]]
Output: [4,3,1,1]
Explanation:
Query [0, 3] → Substring "0100" → Augmented to "101001"
Choose "0100", convert "0100" → "0000" → "1111".
The final string without augmentation is "1111". The maximum number of active sections is 4.
Query [0, 2] → Substring "010" → Augmented to "10101"
Choose "010", convert "010" → "000" → "111".
The final string without augmentation is "1110". The maximum number of active sections is 3.
Query [1, 3] → Substring "100" → Augmented to "11001"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
Query [2, 3] → Substring "00" → Augmented to "1001"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.

Example 3:
Input: s = "1000100", queries = [[1,5],[0,6],[0,4]]
Output: [6,7,2]
Explanation:
Query [1, 5] → Substring "00010" → Augmented to "1000101"
Choose "00010", convert "00010" → "00000" → "11111".
The final string without augmentation is "1111110". The maximum number of active sections is 6.
Query [0, 6] → Substring "1000100" → Augmented to "110001001"
Choose "000100", convert "000100" → "000000" → "111111".
The final string without augmentation is "1111111". The maximum number of active sections is 7.
Query [0, 4] → Substring "10001" → Augmented to "1100011"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 2.

Example 4:
Input: s = "01010", queries = [[0,3],[1,4],[1,3]]
Output: [4,4,2]
Explanation:
Query [0, 3] → Substring "0101" → Augmented to "101011"
Choose "010", convert "010" → "000" → "111".
The final string without augmentation is "11110". The maximum number of active sections is 4.
Query [1, 4] → Substring "1010" → Augmented to "110101"
Choose "010", convert "010" → "000" → "111".
The final string without augmentation is "01111". The maximum number of active sections is 4.
Query [1, 3] → Substring "101" → Augmented to "11011"
Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 2.

Constraints:
1 <= n == s.length <= 10^5
1 <= queries.length <= 10^5
s[i] is either '0' or '1'.
queries[i] = [li, ri]
0 <= li <= ri < n
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

class SegmentTree
{
private:
    int n;
    vector<int> arr;
    vector<int> seg;

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            seg[p] = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        seg[p] = max(seg[p << 1], seg[p << 1 | 1]);
    }

    int query(int p, int l, int r, int L, int R)
    {
        if (L <= l && r <= R)
        {
            return seg[p];
        }

        int mid = (l + r) >> 1;
        int res = 0;
        if (L <= mid)
        {
            res = max(res, query(p << 1, l, mid, L, R));
        }
        if (R > mid)
        {
            res = max(res, query(p << 1 | 1, mid + 1, r, L, R));
        }

        return res;
    }
public:
    SegmentTree(const vector<int>& arr) :arr(arr)
    {
        n = arr.size();
        seg.resize(n << 2, 0);
        build(1, 0, n - 1);
    }

    int querySegTree(int L, int R)
    {
        if (L > R)
        {
            return 0;
        }

        return this->query(1, 0, n - 1, L, R);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int count1 = count(s.begin(), s.end(), '1');

        vector<int> zeroBlocks;
        vector<int> blocksLeft;
        vector<int> blocksRight;

        int i = 0;
        while (i < n)
        {
            int start = i;
            while (i < n && s[i] == s[start])
            {
                i++;
            }
            if (s[start] == '0')
            {
                zeroBlocks.push_back(i - start);
                blocksLeft.push_back(start);
                blocksRight.push_back(i - 1);
            }
        }

        int m = zeroBlocks.size();
        if (m < 2)
        {
            return vector<int>(queries.size(), count1);
        }

        vector<int> tempSum(m - 1);
        for (int i = 0; i < m - 1; i++)
        {
            tempSum[i] = zeroBlocks[i] + zeroBlocks[i + 1];
        }

        SegmentTree seg(tempSum);
        vector<int> result;

        for (const auto& q : queries)
        {
            int l = q[0];
            int r = q[1];
            int i = lower_bound(blocksRight.begin(), blocksRight.end(), l) - blocksRight.begin();
            int j = upper_bound(blocksLeft.begin(), blocksLeft.end(), r) - blocksLeft.begin() - 1;

            if (i > m - 1 || j < 0 || i >= j)
            {
                result.push_back(count1);
                continue;
            }

            int firstLen = blocksRight[i] - max(blocksLeft[i], l) + 1;
            int lastLen = min(blocksRight[j], r) - blocksLeft[j] + 1;

            if (i + 1 == j)
            {
                int bestGain = firstLen + lastLen;
                result.push_back(count1 + bestGain);
                continue;
            }

            int val1 = firstLen + zeroBlocks[i + 1];
            int val2 = zeroBlocks[j - 1] + lastLen;
            int val3 = seg.querySegTree(i + 1, j - 2);
            int bestGain = max({ val1, val2, val3 });
            result.push_back(count1 + bestGain);
        }

        return result;
    }
};

int main()
{
    string s;
    int n;
    cin >> s;
    cin >> n;
    vector<vector<int>> queries(n, vector<int>(2, 0));
    for (int i = 0; i < n; i++)
    {
        cin >> queries[i][0] >> queries[i][1];
    }

    Solution sol;
    vector<int> result = sol.maxActiveSectionsAfterTrade(s, queries);
    Core::printVectorResult(result);
	return 0;
}