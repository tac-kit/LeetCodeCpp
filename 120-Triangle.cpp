#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<int> dp(triangle[triangle.size()-1]);
        for (int i=triangle.size()-2; i>=0; --i) {
            for (int j=0; j<=i; ++j) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
            }
        }
        return dp[0];
    }
};

int main() {
    Solution s;
    vector<vector<int>> myTri{{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    cout << s.minimumTotal(myTri) << endl;

}