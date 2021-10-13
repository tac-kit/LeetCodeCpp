/*
Solution 1: 层序遍历+隔层倒序
Solution 2: 层序遍历，输出时反转（按正常层序遍历顺序访问结点，在输出到res时判断当前层奇偶性），避免reverse。
Solution 3: 上面两种方法的问题是都是按正常层序遍历顺序访问树的结点，应该在遍历时就按Zigzag顺序访问结点，使用双栈实现。
https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/discuss/33904/JAVA-Double-Stack-Solution
*/

#include<iostream>
#include<vector>
#include<deque>
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
    // Solution 1
    // vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    //     vector<TreeNode*> level{root};
    //     vector<vector<int>> resList;
    //     int state=0;
    //     while (root != nullptr && !level.empty()) {
    //         vector<int> res;
    //         for (auto node: level) {
    //             res.push_back(node->val);
    //         }
    //         // 只需要倒序res，newLevel始终是正序
    //         if (state == 0) {
    //             state = 1;
    //         }else{
    //             reverse(res.begin(), res.end());
    //             state = 0;
    //         }
    //         resList.push_back(res);

    //         vector<TreeNode*> newLevel;
    //         for (auto node: level) {
    //             if (node->left != nullptr) {
    //                 newLevel.push_back(node->left);
    //             }
    //             if (node->right != nullptr) {
    //                 newLevel.push_back(node->right);
    //             }
    //         }
    //         level = newLevel;
    //     }
    //     return resList;
    // }

    // Solution 2
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        deque<TreeNode*> nodeQueue{root};  // 使用队列存储结点
        vector<vector<int>> resList;
        int isLeftToRight = 1;
        while(root != nullptr && !nodeQueue.empty()) {
            int levelSize = nodeQueue.size();  // 每次迭代开头存储当前队列长度，作为当前层的长度
            deque<int> resQueue;  // 每层的结果也使用queue存储，通过push_front和push_back实现倒序
            for (int i=0; i<levelSize; ++i) {
                TreeNode *node = nodeQueue.front();
                nodeQueue.pop_front();
                if (isLeftToRight == 1) {
                    resQueue.push_back(node->val);
                }else{
                    resQueue.push_front(node->val);
                }
                
                if (node->left) {
                    nodeQueue.push_back(node->left);
                }
                if (node->right) {
                    nodeQueue.push_back(node->right);
                }
            }
            isLeftToRight = isLeftToRight==1 ? 0 : 1;
            resList.push_back(vector<int>(resQueue.begin(), resQueue.end()));
        }
        return resList;
    }
};

class Solution3 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        stack<TreeNode*> l2rStack, r2lStack;
        vector<vector<int>> resVec;
        if (root == nullptr) return resVec;
        l2rStack.push(root);
        while (!l2rStack.empty()) {
            vector<int> res;
            while (!l2rStack.empty()) {
                TreeNode *node = l2rStack.top();
                l2rStack.pop();
                res.push_back(node->val);
                if (node->left) r2lStack.push(node->left);
                if (node->right) r2lStack.push(node->right);
            }
            resVec.push_back(res);
            
            res.clear();
            while (!r2lStack.empty()) {
                TreeNode *node = r2lStack.top();
                r2lStack.pop();
                res.push_back(node->val);
                if (node->right) l2rStack.push(node->right);
                if (node->left) l2rStack.push(node->left);
            }
            if (!res.empty()) resVec.push_back(res);
        }
        return resVec;
    }
};

void printVec(const vector<int>& vec) {
    for_each(vec.cbegin(), vec.cend(), [](int num){cout << num << " ";});
    cout << endl;
}

int main() {
    Solution s;
    TreeNode *tree = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    s.zigzagLevelOrder(tree);

    Solution3 s3;
    auto res = s3.zigzagLevelOrder(tree);
    for (auto line: res) printVec(line);
}