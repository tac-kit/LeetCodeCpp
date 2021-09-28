/*
Solution 1: 并查集，每个点与它上面和左边的点连接。
如果当前点为0，跳过；如果当前点为1，如果上面和左边至多1个1，直接连接；如果上面
和左边有2个1，如果属于同一个岛，连接；如果属于不同的岛，连接后合并。
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty())
            return 0;
        int columnCnt = grid[0].size();

        unionFind.resize(grid.size() * columnCnt);  // 默认值0

        for (int i=0; i<grid.size(); ++i) {
            for (int j=0; j<columnCnt; ++j) {
                if (grid[i][j] == '1') {
                    unionFind[i*columnCnt+j] = -1;
                    if (i > 0 && grid[i-1][j] == '1') {
                        if (j > 0 && grid[i][j-1] == '1') {
                            // 如果左边和上面都是1
                            // 先将当前点合并到上面
                            int root1 = findRoot((i-1)*columnCnt + j);
                            combine(root1, i*columnCnt+j);
                            root1 = findRoot((i-1)*columnCnt + j);
                            // 再将左边和上面合并（如果二者不属于一个岛）
                            int root2 = findRoot(i*columnCnt + j - 1);
                            if (root1 != root2) combine(root1, root2);
                        }else{
                            // 如果左边是0上面是1
                            int root1 = findRoot((i-1)*columnCnt + j);
                            combine(root1, i*columnCnt+j);
                        }
                    }else{
                        if (j > 0 && grid[i][j-1] == '1') {
                            // 如果左边是1上面是0
                            int root2 = findRoot(i*columnCnt + j - 1);
                            combine(root2, i*columnCnt+j);
                        }
                    }
                }
            }
        }
        // 根结点计数
        int res=0;
        for (int num: unionFind) {
            if (num < 0) res++;
        }
        return res;
    }

private:
    vector<int> unionFind;
    int findRoot(int idx) {
        int oldIdx = idx;
        while (unionFind[idx] >= 0) idx = unionFind[idx];
        if (unionFind[oldIdx] > 0) unionFind[oldIdx] = idx;  // 路径压缩
        return idx;
    }

    void combine(int idx1, int idx2) {
        if (unionFind[idx1] < unionFind[idx2]) {
            unionFind[idx1] += unionFind[idx2];
            unionFind[idx2] = idx1;
        }else{
            unionFind[idx2] += unionFind[idx1];
            unionFind[idx1] = idx2;
        }
    }
};

int main() {
    Solution s;
    vector<vector<char>> testVec1{{'0','1'}, {'1', '0'}};
    cout << s.numIslands(testVec1) << endl;

    vector<vector<char>> testVec2{{'1', '1', '1', '1', '0'}, 
                                {'1', '1', '0', '1', '0'}, 
                                {'1', '1', '0', '0', '0'}, 
                                {'0', '0', '0', '0', '0'}};
    cout << s.numIslands(testVec2) << endl;

    vector<vector<char>> testVec3{{'1', '1', '0', '0', '0'}, 
                                {'1', '1', '0', '0', '0'}, 
                                {'0', '0', '1', '0', '0'}, 
                                {'0', '0', '0', '1', '1'}};
    cout << s.numIslands(testVec3) << endl;

    // 测试是否在合并前检查是否属于一个岛
    vector<vector<char>> testVec4{{'1', '1', '1', '1', '0'}, 
                                {'1', '0', '0', '1', '1'}, 
                                {'1', '1', '1', '1', '0'}, 
                                {'0', '1', '0', '1', '1'}};
    cout << s.numIslands(testVec4) << endl;
}