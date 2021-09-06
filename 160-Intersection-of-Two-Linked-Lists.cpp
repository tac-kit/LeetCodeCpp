/*
NOTE: 
这道题应该如何处理指针的交换？使用状态变量记忆？
Solution 1: 双指针。因为想到“遍历完A之后遍历B，那遍历B之后是不是要回到A？”，所以添加了state表示状态，其实是不需要的。一共只遍历一轮。
Solution 1.1: 双指针，去掉状态。
*/

#include<iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Solution 1
    // ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    //     if (headA==nullptr || headB==nullptr) {
    //         return nullptr;
    //     }
    //     ListNode *currA = headA, *currB = headB;
    //     int stateA=0, stateB=1;
    //     while (currA != currB) {
    //         if (currA == nullptr) {
    //             if (stateA == 0) {
    //                 currA = headB;
    //                 stateA = 1;
    //             }else{
    //                 currA = headA;
    //                 stateA = 0;
    //             }
    //         }
    //         if (currB == nullptr) {
    //             if (stateB == 0) {
    //                 currB = headB;
    //                 stateB = 1;
    //             }else{
    //                 currB = headA;
    //                 stateB = 0;
    //             }
    //         }
    //         currA = currA->next;
    //         currB = currB->next;
    //     }
    //     return currA;
    // }

    // Solution 1.1
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *currA = headA, *currB = headB;
        while (currA != currB) {
            currA = currA==nullptr ? headB : currA->next;
            currB = currB==nullptr ? headA : currB->next;
        }
        return currA;
    }
};

int main() {
    Solution s;

}