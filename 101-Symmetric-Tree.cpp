/*
Solution 1: 迭代，左右分别中序遍历（左中右、右中左），比对结构和数值是否相同。
Solution 2: 递归。
https://leetcode.com/problems/symmetric-tree/discuss/33054/Recursive-and-non-recursive-solutions-in-Java
*/

#include<iostream>
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

// class Solution {
// public:
//     bool isSymmetric(TreeNode* root) {
//         TreeNode *leftCurr=root->left, *rightCurr=root->right;
//         stack<TreeNode*> leftS, rightS;
//         while ((leftCurr!=nullptr || !leftS.empty()) && (rightCurr!=nullptr || !rightS.empty())) {
//             while (leftCurr!=nullptr && rightCurr!=nullptr) {
//                 leftS.push(leftCurr);
//                 leftCurr = leftCurr->left;
//                 rightS.push(rightCurr);
//                 rightCurr = rightCurr->right;
//             }
//             if (leftCurr!=nullptr || rightCurr!=nullptr)
//                 return false;
//             leftCurr = leftS.top();
//             rightCurr = rightS.top();
//             if (leftCurr->val != rightCurr->val)
//                 return false;
//             leftS.pop();
//             rightS.pop();
//             leftCurr = leftCurr->right;
//             rightCurr = rightCurr->left;
//         }
//         return !((leftCurr!=nullptr || !leftS.empty()) || (rightCurr!=nullptr || !rightS.empty()));
//     }
// };

// Solution 2
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        return helper(root->left, root->right);
    }

private:
    // 递归函数两个参数，实现左右子树分别递归遍历
    bool helper(TreeNode *left, TreeNode *right) {
        if (left==nullptr || right==nullptr)
            return left == right;
        else if (left->val != right->val)
            return false;
        else
            return helper(left->left, right->right) && helper(left->right, right->left);
    }
};

int main() {
    Solution s;
    TreeNode *tree = new TreeNode(1, new TreeNode(2, new TreeNode(3), new TreeNode(4)), new TreeNode(2, new TreeNode(4), new TreeNode(3)));
    cout << s.isSymmetric(tree) << endl;
}