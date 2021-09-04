/*
Solution 1: 双指针
*/

#include<iostream>
#include<cassert>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prevNode = nullptr, *currNode = head;
        while (currNode != nullptr) {
            ListNode *tempNode = currNode->next;
            currNode->next = prevNode;
            prevNode = currNode;
            currNode = tempNode;
        }
        return prevNode;
    }
};

int main() {
    auto printList = [](ListNode* nodePtr){while (nodePtr != nullptr){cout << nodePtr->val << endl; nodePtr=nodePtr->next;}};
    Solution s;
    ListNode *myListPtr = new ListNode(1, new ListNode(2));
    ListNode *retListPtr = s.reverseList(myListPtr);
    printList(retListPtr);
}