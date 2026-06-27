#pragma once
#include<iostream>
#include<vector>
#include <queue>
#include<string>
using namespace std;

class TreeNode
{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};

class ListNode
{
public:
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Core
{
private:
public:
	template<typename T>
	static void printVectorResult(vector<T> result)
	{
		for (int i=0;i<result.size(); i++)
		{
			if (i == result.size() - 1)
			{
				cout << result[i];
			}
			else
			{
				cout << result[i] << " ";
			}
		}
	}

    static void printBinaryTreeInLevelOrder(TreeNode* root)
    {
        if (!root)
        {
            cout << "\n";
            return;
        }

        queue<TreeNode*> q;
        q.push(root);
        vector<string> result;

        // Standard BFS Traversal
        while (!q.empty())
        {
            TreeNode* current = q.front();
            q.pop();

            if (current)
            {
                result.push_back(to_string(current->val));
                // Push children even if they are null (clean trailing nulls later)
                q.push(current->left);
                q.push(current->right);
            }
            else
            {
                result.push_back("null");
            }
        }

        // Clean up trailing "null"s to match LeetCode's compact format
        while (!result.empty() && result.back() == "null")
        {
            result.pop_back();
        }

        // Print the output
        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i] << " ";
        }
        cout << "\n";
    }

    // Method to generate a Linked List from a vector
    static ListNode* createLinkedList(const vector<int>& nums)
    {
        if (nums.empty())
        {
            return nullptr;
        }

        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        for (int num : nums)
        {
            current->next = new ListNode(num);
            current = current->next;
        }

        ListNode* head = dummy->next;
        delete dummy;
        return head;
    }

    static void printList(ListNode* head)
    {
        ListNode* node = head;
        while (node)
        {
            cout << node->val << (node->next?" ":"");
            node = node->next;
        }
    }
};