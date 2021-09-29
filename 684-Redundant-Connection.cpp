/*
Solution 1: 并查集，树是无环图，因此只要去掉edges中环上的任意一条边，就能变成树。
去掉edges中任意一条边有两个结果：变成一个树，或变成两个图。因此可以遍历edges，尝试去掉每条边，通过并查集看连通分量有几个。
Solution 2: 并查集。环在合拢时，两边属于同一个连通分量，也就是在并查集判断idx1与idx2是否可以合并时，会发现二者相等不能合并。
只要将出现不能合并情况的edge返回即可，这就是为什么原题要求返回满足条件的最后一个edge。
Solution 2.1: 基于官方解答的并查集实现，包含union by rank和path compression。
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // 树的边数是结点数减1，考虑多1条边，同时结点从1开始编号。负数表示为双亲结点，绝对值代表连通分量结点数。
        unionFind = vector<int>(edges.size()+1, -1);
        for (auto edge: edges) {
            int idx1 = find(edge[0]);
            int idx2 = find(edge[1]);
            if (idx1 != idx2) {
                combine(idx1, idx2);
            }else{
                return edge;
            }
        }
        return {};
    }

private:
    vector<int> unionFind;
    int find(int idx) {
        while (unionFind[idx] > 0) idx = unionFind[idx];
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

class Solution21 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        // 初始化
        parent = vector<int>(edges.size()+1, 0);
        rank = vector<int>(edges.size()+1, 0);  // 秩初始化为零
        for (int i=0; i<=edges.size(); ++i) parent[i] = i;  // 将parent初始化为指向自己

        // 遍历
        for (auto edge: edges) {
            int idx1 = find(edge[0]);
            int idx2 = find(edge[1]);
            if (idx1 != idx2) {
                combine(idx1, idx2);
            }else{
                return edge;
            }
        }
        return {};
    }
private:
    vector<int> parent;  // 双亲结点或根结点
    vector<int> rank;  // 当前连通分量的高度（秩）

    int find(int idx) {
        // 【路径压缩】递归实现，使得搜索路径上所有结点全部指向根结点
        if (idx != parent[idx]) parent[idx] = find(parent[idx]);
        return parent[idx];  // 注意这种实现要返回parent[idx]
    }

    void combine(int idx1, int idx2) {
        // 【按秩合并】
        if (rank[idx1] < rank[idx2]) parent[idx1] = idx2;
        else if (rank[idx1] > rank[idx2]) parent[idx2] = idx1;
        else {
            parent[idx1] = idx2;
            rank[idx2]++;  // 只有在两边秩相等时才自增
        }
    }
};

void printVec(const vector<int>& vec) {
    for_each(vec.cbegin(), vec.cend(), [](int num){cout << num << " ";});
    cout << endl;
}

int main() {
    Solution s;
    vector<vector<int>> myVec{{1,2}, {1,3}, {2,3}};
    auto res = s.findRedundantConnection(myVec);
    printVec(res);
}