/*
Tags
level-hard
array, string, trie

Problem Description
3093. Longest Common Suffix Queries
You are given two arrays of strings wordsContainer and wordsQuery.
For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i].
If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length.
If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.
Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].

Example 1:
Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
Output: [1,1,1]
Explanation:
Let's look at each wordsQuery[i] separately:
For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2.
Among these, the answer is the string at index 1 because it has the shortest length of 3.

Example 2:
Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]
Output: [2,0,2]
Explanation:
Let's look at each wordsQuery[i] separately:
For wordsQuery[0] = "gh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
For wordsQuery[1] = "acbfgh", only the string at index 0 shares the longest common suffix "fgh". Hence it is the answer, even though the string at index 2 is shorter.
For wordsQuery[2] = "acbfegh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.

Constraints:
1 <= wordsContainer.length, wordsQuery.length <= 10^4
1 <= wordsContainer[i].length <= 5 * 10^3
1 <= wordsQuery[i].length <= 5 * 10^3
wordsContainer[i] consists only of lowercase English letters.
wordsQuery[i] consists only of lowercase English letters.
Sum of wordsContainer[i].length is at most 5 * 10^5.
Sum of wordsQuery[i].length is at most 5 * 10^5.

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
#include<cstring>
#include<climits>
#include "../../core/core.h"
using namespace std;

// Getting TLE in leetcode
//class TrieNode
//{
//public:
//    int minIndex;
//    int minLength;
//    TrieNode* children[26];
//    TrieNode()
//    {
//        this->minIndex = INT_MAX;
//        this->minLength = INT_MAX;
//        for (int i = 0; i < 26; i++)
//        {
//            this->children[i] = nullptr;
//        }
//    }
//};
//
//class Trie
//{
//public:
//    TrieNode* root;
//    Trie()
//    {
//        this->root = new TrieNode();
//    }
//
//    void insert(string word, int index)
//    {
//        int len = word.length();
//        TrieNode* node = this->root;
//        if (len < node->minLength)
//        {
//            node->minLength = len;
//            node->minIndex = index;
//        }
//        for (char ch : word)
//        {
//            int c = ch - 'a';
//            if (node->children[c] == nullptr)
//            {
//                node->children[c] = new TrieNode();
//            }
//            node = node->children[c];
//
//            if (len < node->minLength)
//            {
//                node->minLength = len;
//                node->minIndex = index;
//            }
//        }
//    }
//
//    int query(string word)
//    {
//        TrieNode* node = this->root;
//        for (char ch : word)
//        {
//            int c = ch - 'a';
//            if (node->children[c] != nullptr)
//            {
//                node = node->children[c];
//            }
//            else
//            {
//                break;
//            }
//        }
//
//        return node->minIndex;
//
//    }
//};
//class Solution {
//public:
//    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery)
//    {
//        Trie trie;
//        int m = wordsContainer.size();
//        int n = wordsQuery.size();
//
//        for (int i = 0; i < m; i++)
//        {
//            string word = wordsContainer[i];
//            reverse(word.begin(), word.end());
//            trie.insert(word, i);
//        }
//
//        vector<int> result(n);
//        for (int i = 0; i < n; i++)
//        {
//            string word = wordsQuery[i];
//            reverse(word.begin(), word.end());
//            result[i] = trie.query(word);
//        }
//
//        return result;
//    }
//};


class Trie
{
private:
    static constexpr int N = 500010, M = 26;
    int totalTrieNode;
    int trie[N][M];
    int minLength[N];
    int minIndex[N];
public:
    Trie() :totalTrieNode(0)
    {
        for (int i = 0; i < N; i++)
        {
            memset(trie[i], 0, sizeof(trie[i]));
            minLength[i] = INT_MAX;
            minIndex[i] = INT_MAX;
        }
    }
    void clear()
    {
        for (int i = 0; i <= totalTrieNode; i++)
        {
            memset(trie[i], 0, sizeof(trie[i]));
            minLength[i] = INT_MAX;
            minIndex[i] = INT_MAX;
        }
        totalTrieNode = 0;
    }

    void insert(string s, int index)
    {
        // Starting from the root node.
        int node = 0;
        if (s.length() < minLength[node])
        {
            minLength[node] = s.length();
            minIndex[node] = index;
        }
        for (auto& ch : s)
        {
            int c = ch - 'a';
            if (trie[node][c] == 0)
            {
                trie[node][c] = ++totalTrieNode;
            }
            node = trie[node][c];
            if (s.length() < minLength[node])
            {
                minLength[node] = s.length();
                minIndex[node] = index;
            }
        }
    }

    int query(string s)
    {
        int node = 0;
        for (auto& ch : s)
        {
            int c = ch - 'a';
            if (trie[node][c] != 0)
            {
                node = trie[node][c];
            }
            else
            {
                break;
            }
        }

        return minIndex[node];
    }
};

Trie trie;

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        trie.clear();
        int n = wordsContainer.size();
        int m = wordsQuery.size();
        for (int i = 0; i < n; i++)
        {
            string s = wordsContainer[i];
            reverse(s.begin(), s.end());
            trie.insert(s, i);
        }

        vector<int> result(m);
        for (int i = 0; i < m; i++)
        {
            string s = wordsQuery[i];
            reverse(s.begin(), s.end());
            result[i] = trie.query(s);
        }

        return result;
    }
};

int main()
{
    vector<string> wordsContainer, vectorwordsQuery;
    int n, m;
    string s;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        wordsContainer.push_back(s);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        vectorwordsQuery.push_back(s);
    }
    Solution sol;
    vector<int> result = sol.stringIndices(wordsContainer, vectorwordsQuery);
    Core::printVectorResult(result);
	return 0;
}