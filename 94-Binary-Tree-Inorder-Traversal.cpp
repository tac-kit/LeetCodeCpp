/*
Solution 1: 递归
Solution 2: 迭代
*/

#include<iostream>
#include<vector>
#include<stack>
#include<cassert>
#include<algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // Solution 1
    // vector<int> inorderTraversal(TreeNode* root) {
    //     if (root == nullptr){
    //         return vector<int>{};
    //     }
    //     vector<int> left_res = this->inorderTraversal(root->left);
    //     vector<int> right_res = this->inorderTraversal(root->right);
    //     vector<int> res;
    //     copy(left_res.begin(), left_res.end(), back_inserter(res));
    //     res.push_back(root->val);
    //     copy(right_res.begin(), right_res.end(), back_inserter(res));
    //     return res;
    // }

    // Solution 2
    vector<int> inorderTraversal(TreeNode* root){
        stack<TreeNode*> s;
        vector<int> res;
        while (root!=nullptr || !s.empty()){
            while (root!=nullptr){
                s.push(root);
                root=root->left;
            }
            root=s.top();
            s.pop();
            res.push_back(root->val);
            root=root->right;
        }
        return res;
    }
};

int main()
{
    auto print_vec = [](int a){cout << a << endl;};
    TreeNode *tree = new TreeNode(1);
    tree->right = new TreeNode(2);
    tree->right->left = new TreeNode(3);
    Solution s;
    vector<int> res = s.inorderTraversal(tree);
    for_each(res.begin(), res.end(), print_vec);
    vector<int> ans{1,3,2};
    for_each(ans.begin(), ans.end(), print_vec);
    assert(res == ans);
    delete tree;
}