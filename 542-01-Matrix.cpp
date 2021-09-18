/*
Solution 1: 需要考虑4个方向是否有零，应该与接雨水类似，可以使用4个不同方向的DP合并。
Solution 1.1: 答案只考虑了NW与SE两个方向，因为它是在同一个DP上修改的，因此在计算
NW的结果会影响SE，也就间接考虑了NE和SW两个方向。详见
https://leetcode.com/problems/01-matrix/solution/1029397
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        // nw表示从左上角开始
        vector<vector<int>> nwDP(mat.size(), vector<int>(mat[0].size(), 0));
        vector<vector<int>> neDP(mat.size(), vector<int>(mat[0].size(), 0));
        vector<vector<int>> swDP(mat.size(), vector<int>(mat[0].size(), 0));
        vector<vector<int>> seDP(mat.size(), vector<int>(mat[0].size(), 0));

        for (int i=0; i<mat.size(); ++i) {
            for (int j=0; j<mat[i].size(); ++j) {
                if (mat[i][j] != 0) {
                    int leftCell = j > 0 ? nwDP[i][j-1] : 100000;
                    int upCell = i > 0 ? nwDP[i-1][j] : 100000;
                    nwDP[i][j] = min(leftCell, upCell) + 1;
                }
            }
        }

        for (int i=0; i<mat.size(); ++i) {
            for (int j=mat[i].size()-1; j>=0; --j) {
                if (mat[i][j] != 0) {
                    int rightCell = j < mat[i].size()-1 ? neDP[i][j+1] : 100000;
                    int upCell = i > 0 ? neDP[i-1][j] : 100000;
                    neDP[i][j] = min(rightCell, upCell) + 1;
                }
            }
        }

        for (int i=mat.size()-1; i>=0; --i) {
            for (int j=0; j<mat[i].size(); ++j) {
                if (mat[i][j] != 0) {
                    int leftCell = j > 0 ? swDP[i][j-1] : 100000;
                    int downCell = i < mat.size()-1 ? swDP[i+1][j] : 100000;
                    swDP[i][j] = min(leftCell, downCell) + 1;
                }
            }
        }

        for (int i=mat.size()-1; i>=0; --i) {
            for (int j=mat[i].size()-1; j>=0; --j) {
                if (mat[i][j] != 0) {
                    int rightCell = j < mat[i].size()-1 ? seDP[i][j+1] : 100000;
                    int downCell = i < mat.size()-1 ? seDP[i+1][j] : 100000;
                    seDP[i][j] = min(rightCell, downCell) + 1;
                }
            }
        }

        vector<vector<int>> DP(mat.size(), vector<int>(mat[0].size(), 0));
        for (int i=0; i<mat.size(); ++i) {
            for (int j=0; j<mat[i].size(); ++j) {
                // NOTE: std::min通过初始化列表实现多参数比较最小值
                DP[i][j] = min({nwDP[i][j], neDP[i][j], swDP[i][j], seDP[i][j]});
            }
        }
        return DP;
    }
};

void printVec(const vector<int>& vec) {
    for_each(vec.cbegin(), vec.cend(), [](int num){cout << num << " ";});
    cout << endl;
}

int main() {
    Solution s;
    vector<vector<int>> myVec{{0,0,0}, {0,1,0}, {0,0,0}};
    vector<vector<int>> res = s.updateMatrix(myVec);
    for_each(res.cbegin(), res.cend(), printVec);
}