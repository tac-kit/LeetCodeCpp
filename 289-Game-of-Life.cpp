/*
Solution 1: 原地算法，通过位运算实现，第0位标记原矩阵，第1位标记新矩阵。
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Q: 如何表示矩阵？A: vector<vector<int>>
    void gameOfLife(vector<vector<int>>& board) {
        // Q: 如何表示坐标？A: pair<int, int>
        vector<pair<int, int>> neighbor_table{{-1, -1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
        for (int row_idx=0; row_idx<board.size(); ++row_idx){
            for (int col_idx=0; col_idx<board[0].size(); ++col_idx){
                int live_neighbors_cnt = 0;
                for (pair<int, int> neighbor: neighbor_table){
                    // NOTE: pair不是通过下标而是通过first和second访问元素
                    int neighbor_row = row_idx + neighbor.first;
                    int neighbor_col = col_idx + neighbor.second;
                    if (neighbor_row>=0 && neighbor_row<board.size()
                        && neighbor_col>=0 && neighbor_col<board[0].size()
                        && (board[neighbor_row][neighbor_col]&1) == 1)
                        live_neighbors_cnt++;                        
                }
                if ((board[row_idx][col_idx]&1) == 1){
                    // live cell
                    // Any live cell with two or three live neighbors lives on to the next generation.
                    if (live_neighbors_cnt >= 2 && live_neighbors_cnt <= 3)
                        board[row_idx][col_idx] |= 2;
                }else{
                    // dead cell
                    // Any dead cell with exactly three live neighbors becomes a live cell.
                    if (live_neighbors_cnt == 3)
                        board[row_idx][col_idx] |= 2;
                }
            }
        }
        // 将所有第1位为1的标记为1
        // for (int row_idx=0; row_idx<board.size(); ++row_idx){
        //     for (int col_idx=0; col_idx<board[0].size(); ++col_idx){
        //         // NOTE: 按位与&优先级低于==，需要加括号
        //         if ((board[row_idx][col_idx] & 2) == 2){
        //             board[row_idx][col_idx] = 1;
        //         }else{
        //             board[row_idx][col_idx] = 0;
        //         }
        //     }
        // }
        // 可优化为右移一位
        for (int row_idx=0; row_idx<board.size(); ++row_idx)
            for (int col_idx=0; col_idx<board[0].size(); ++col_idx)
                board[row_idx][col_idx] >>= 1;
    }
};

int main(){
    Solution s;
    vector<vector<int>> tc1{{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
    vector<vector<int>> res1{{0,0,0},{1,0,1},{0,1,1},{0,1,0}};
    s.gameOfLife(tc1);
    // Q: 如何判断两个矩阵相等？A: 两重循环。
    bool valid_flag=true;
    for (int i=0; i<tc1.size(); ++i){
        for (int j=0; j<tc1[0].size(); ++j){
            if (tc1[i][j] != res1[i][j]){
                // cout << tc1[i][j] << " " << res1[i][j] << endl;
                // cout << "wrong answer" << endl;
                valid_flag=false;
            }
        }
    }
    cout << valid_flag << endl;
}