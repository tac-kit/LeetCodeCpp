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
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode *curr=root, *prev=nullptr;
        stack<TreeNode*> s;
        vector<int> res;
        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            // 注意判断条件要判断是否存在右子树，然后再判断右子树是否访问过
            if (curr->right != nullptr && curr->right != prev) {
                s.push(curr);
                curr = curr->right;
            }else{
                res.push_back(curr->val);
                prev = curr;
                curr = nullptr;
            }
            // 错误写法
            // if (curr->right == prev) {
            //     res.push_back(curr->val);
            //     prev = curr;
            //     curr = nullptr;
            // }else{
            //     s.push(curr);
            //     curr = curr->right;
            // }
        }
        return res;
    }
};

void printVec(const vector<int>& vec) {
    for_each(vec.begin(), vec.end(), [](int num){cout << num << " ";});
    cout << endl;
}

int main() {
    Solution s;
    TreeNode *tree = new TreeNode(1, nullptr, new TreeNode(2, new TreeNode(3), nullptr));
    vector<int> res = s.postorderTraversal(tree);
    printVec(res);
}