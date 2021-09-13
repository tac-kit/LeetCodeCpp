#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, const vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> preDict;
        for (int i=0; i<numCourses; ++i) {
            preDict[i] = vector<int>();
        }
        for (auto pre: prerequisites) {
            preDict[pre[0]].push_back(pre[1]);
        }
        vector<int> res;
        // 每访问一个结点就从preDict中删除，当preDict为空时说明所有结点都访问过。
        while (preDict.size() > 0) {
            int breakFlag = false;
            // 查找入度为零的结点
            for (int course=0; course < numCourses; ++course) {
                auto iter = preDict.find(course);
                if (iter == preDict.end())
                    continue;
                // 从其它结点的列表中删除入度为零的结点
                if (iter->second.size() == 0) {
                    res.push_back(iter->first);
                    // Q: 如何删除字典值向量中的元素？使用erase-remove
                    for (auto deleteIter=preDict.begin(); deleteIter!=preDict.end(); ++deleteIter) {
                        deleteIter->second.erase(remove(deleteIter->second.begin(), deleteIter->second.end(), iter->first), deleteIter->second.end());
                    }
                    preDict.erase(course);
                    breakFlag = true;
                    break;
                }
            }
            // If it is impossible to finish all courses, return an empty array.
            if (!breakFlag)
                return vector<int>();
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
    vector<int> res = s.findOrder(2, vector<vector<int>>{{1,0}});
    printVec(res);
}