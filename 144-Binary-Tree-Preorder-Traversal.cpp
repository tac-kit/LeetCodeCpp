#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

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
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> res;
        // 结束标志是root为空且s为空，所以循环条件是存在不为空，逻辑或
        while (root != nullptr || !s.empty()) {
            while(root != nullptr) {
                res.push_back(root->val);
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            root = root->right;
        }
        return res;
    }
};

int main() {
    Solution s;
    TreeNode *tree = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));
    vector<int> res = s.preorderTraversal(tree);
    for_each(res.cbegin(), res.cend(), [](int num){cout << num << " ";});
}