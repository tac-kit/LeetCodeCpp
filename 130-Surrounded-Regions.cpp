/*
Solution 1: BFS，遍历所有边界点，以边界点为起点BFS连通的"O"，置为"S"。
之后将所有剩余的"O"置为"X"，再将所有"S"置为"O"。Time Limit Exceeded
TODO: 为什么BFS会超时？
Solution 2: 并查集，使用第3个向量保存所有集合是否与边界连通。
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

class Solution1 {
public:
    void solve(vector<vector<char>>& board) {
        // 遍历4条边界
        for (int i=0; i<board[0].size(); ++i) {
            if (board[0][i] == 'O') bfs(board, 0, i);
        }
        for (int i=0; i<board.size(); ++i) {
            if (board[i][board[0].size()-1] == 'O') bfs(board, i, board[0].size()-1);
        }
        for (int i=0; i<board.size(); ++i) {
            if (board[i][0] == 'O') bfs(board, i, 0);
        }
        for (int i=0; i<board[0].size(); ++i) {
            if (board[board.size()-1][i] == 'O') bfs(board, board.size()-1, i);
        }

        for (int i=0; i<board.size(); ++i) {
            for (int j=0; j<board[0].size(); ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == 'S') board[i][j] = 'O';
            }
        }
    }

private:
    void bfs(vector<vector<char>>& board, int x, int y) {
        queue<pair<int, int>> q;
        q.emplace(x, y);
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            board[node.first][node.second] = 'S';
            if (node.first > 0 && board[node.first-1][node.second] == 'O') q.emplace(node.first-1, node.second);
            if (node.first < board.size()-1 && board[node.first+1][node.second] == 'O') q.emplace(node.first+1, node.second);
            if (node.second > 0 && board[node.first][node.second-1] == 'O') q.emplace(node.first, node.second-1);
            if (node.second < board[0].size()-1 && board[node.first][node.second+1] == 'O') q.emplace(node.first, node.second+1);
        }
    }
};

class Solution2 {
public:
    void solve(vector<vector<char>>& board) {
        parent = vector<int>(board.size()*board[0].size(), 0);
        rank = vector<int>(board.size()*board[0].size(), 0);
        isBorder = vector<int>(board.size()*board[0].size(), 0);
        for (int i=0; i<parent.size(); ++i) parent[i] = i;

        int width = board[0].size();
        for (int i=0; i<board.size(); ++i) {
            for (int j=0; j<width; ++j) {
                if (board[i][j] == 'O') {
                    int idx = i*width+j;
                    if (i==0 || i==board.size()-1 || j==0 || j==width-1) {
                        isBorder[idx] = 1;
                    }
                    if (i>0 && board[i-1][j] == 'O') {
                        int idx1 = find((i-1)*width+j);
                        combine(idx, idx1);
                        if (j>0 && board[i][j-1] == 'O') {
                            idx1 = find((i-1)*width+j);
                            int idx2 = find(i*width+j-1);
                            combine(idx1, idx2);
                        }
                    }else{
                        if (j>0 && board[i][j-1] == 'O') {
                            int idx2 = find(i*width+j-1);
                            combine(idx, idx2);
                        }
                    }
                }
            }
        }

        // 刷新根结点isBorder结果。下面两个循环不能合并。
        for (int i=0; i<board.size(); ++i) {
            for (int j=0; j<width; ++j) {
                if (board[i][j] == 'O') {
                    int par = find(i*width+j);
                }
            }
        }

        for (int i=0; i<board.size(); ++i) {
            for (int j=0; j<width; ++j) {
                if (board[i][j] == 'O') {
                    int par = find(i*width+j);
                    if (isBorder[par] == 0) {
                        board[i][j] = 'X';
                    }
                }
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
    vector<int> isBorder;

    int find(int idx) {
        // NOTE: 这里是if不是while
        if (parent[idx] != idx) {
            if (isBorder[idx] == 1) {
                isBorder[parent[idx]] = 1;
            }
            parent[idx] = find(parent[idx]);
        }
        return parent[idx];
    }

    void combine(int idx1, int idx2) {
        if (idx1 == idx2) return;
        if (rank[idx1] == rank[idx2]) {
            parent[idx1] = idx2;
            rank[idx2]++;
        }else if (rank[idx1] < rank[idx2]) {
            parent[idx1] = idx2;
        }else{
            parent[idx2] = idx1;
        }
    }
};

void printVec(const vector<char>& charVec) {
    for_each(charVec.cbegin(), charVec.cend(), [](char c){cout << c << " ";});
    cout << endl;
}

int main() {
    Solution1 s1;
    vector<vector<char>> myVec{{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    s1.solve(myVec);
    for (auto vec: myVec) printVec(vec);

    Solution2 s2;
    vector<vector<char>> myVec2{{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    s2.solve(myVec2);
    for (auto vec: myVec2) printVec(vec);

    vector<vector<char>> myVec3{{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'O', 'X', 'X'}, {'O', 'O', 'X', 'X'}};
    s2.solve(myVec3);
    for (auto vec: myVec3) printVec(vec);
}