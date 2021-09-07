/*
Solution 1: 递归，将当前结点及两个子树视为3个单元，如果恰好有2个单元存在匹配结点，则当前结点为LCA。
*/

#include<iostream>
#include<cassert>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        helper(root, p, q);
        return common;
    }
private:
    TreeNode* common = nullptr;

    int helper(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) {
            return 0;
        }else{
            int ret = 0;
            if (root == p || root == q) {
                ret += 1;
            }
            ret += helper(root->left, p, q);
            ret += helper(root->right, p, q);
            if (ret == 2) {
                common = root;
            }
            return ret > 0 ? 1 : 0;
        }
    }
};

int main() {
    Solution s;
    TreeNode *node1 = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    node1->left = node2;
    node1->right = node3;
    assert(s.lowestCommonAncestor(node1, node2, node3) == node1);
}