#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        vector<int> line{1};
        res.push_back(line);
        for (int i=1; i<numRows; ++i) {
            vector<int> newLine{1};
            for (int j=1; j<line.size(); ++j) {
                newLine.push_back(line[j-1] + line[j]);
            }
            newLine.push_back(1);
            line = newLine;
            res.push_back(newLine);
        }
        return res;
    }
};

void printVec(const vector<int>& vec) {
    for_each(vec.cbegin(), vec.cend(), [](int num){cout << num << " ";});
    cout << endl;
}

int main() {
    Solution s;
    vector<vector<int>> res = s.generate(5);
    for (vector<int> line: res) {
        printVec(line);
    }
}