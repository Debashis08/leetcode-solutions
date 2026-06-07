/*
Tags
level-medium
tree, binary-tree, hash-map,


Problem Description
2196. Create Binary Tree From Descriptions
You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,
If isLefti == 1, then childi is the left child of parenti.
If isLefti == 0, then childi is the right child of parenti.
Construct the binary tree described by descriptions and return its root.

The test cases will be generated such that the binary tree is valid.

Example 1:
Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
Output: [50,20,80,15,17,19]
Explanation: The root node is the node with value 50 since it has no parent.
The resulting binary tree is shown in the diagram.

Example 2:
Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
Output: [1,2,null,null,3,4]
Explanation: The root node is the node with value 1 since it has no parent.
The resulting binary tree is shown in the diagram.

Constraints:
1 <= descriptions.length <= 10^4
descriptions[i].length == 3
1 <= parenti, childi <= 10^5
0 <= isLefti <= 1
The binary tree described by descriptions is valid.

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

class Solution {
private:
	unordered_map<int, TreeNode*> nodeMap;
	unordered_set<int> childSet;
public:
	TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
		for (auto& it : descriptions)
		{
			int parent = it[0];
			int child = it[1];
			bool isLeft = it[2];
			if (nodeMap.find(parent) == nodeMap.end())
			{
				nodeMap[parent] = new TreeNode(parent);
			}
			if (nodeMap.find(child) == nodeMap.end())
			{
				nodeMap[child] = new TreeNode(child);
			}
			if (isLeft)
			{
				nodeMap[parent]->left = nodeMap[child];
			}
			else
			{
				nodeMap[parent]->right = nodeMap[child];
			}
			childSet.insert(child);
		}

		for (auto& it : nodeMap)
		{
			auto& val = it.first;
			auto& node = it.second;
			if (childSet.find(val) == childSet.end())
			{
				return node;
			}
		}

		return nullptr;
	}
};

int main()
{
	int n;
	Solution sol;
	vector<vector<int>> description;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int parent, child, isLeft;
		cin >> parent >> child >> isLeft;
		description.push_back({parent, child, isLeft});
	}
	TreeNode* root = sol.createBinaryTree(description);
	Core::printBinaryTreeInLevelOrder(root);
	return 0;
}