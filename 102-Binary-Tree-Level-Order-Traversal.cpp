/*
Solution 1: 使用列表存储层。
Solution 2: (TODO)使用队列实现层序遍历。
*/

#include<iostream>
#include<vector>
#include<cassert>

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        vector<TreeNode*> level{root};
        while (root != nullptr && level.size() > 0) {
            vector<int> levelVal;
            for (auto node: level) {
                levelVal.push_back(node->val);
            }
            res.push_back(levelVal);

            vector<TreeNode*> nextLevel;
            for (auto node: level) {
                if (node->left != nullptr) {
                    nextLevel.push_back(node->left);
                }
                if (node->right != nullptr) {
                    nextLevel.push_back(node->right);
                }
            }
            level = nextLevel;
        }
        return res;
    }
};

int main() {
    Solution s;
    TreeNode *tree = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    auto res = s.levelOrder(tree);
    for (auto line: res) {
        for (auto num: line) {
            cout << num << " ";
        }
        cout << endl;
    }
}