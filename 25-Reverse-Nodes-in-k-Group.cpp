/*
Solution 1: 指针。
step 1: for _ in range(k-1): next=next.next
step 2: prev.next = next
step 3: while curr!=next: reverse(curr, curr.next)

Solution 2: 子问题，将"翻转长度为k的链表"作为子问题交给helper实现，helper返回翻转后链表的首尾指针，将不同组的helper结果首尾拼接。
这个解法的优点是理解起来比较简单，空间复杂度O(1).
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

// Solution 1
// class Solution {
// public:
//     ListNode* reverseKGroup(ListNode* head, int k) {
//         ListNode *dummy = new ListNode();
//         ListNode *prev=dummy, *curr=head, *next=head;
        
//         while (next != nullptr) {
//             // step 1
//             int cnt=1;
//             while (next != nullptr && cnt < k) {
//                 next = next->next;
//                 cnt++;
//             }
//             if (cnt != k || next == nullptr) {
//                 break;
//             }
//             // step 2
//             prev->next = next;
//             next = next->next;
//             prev = curr;
//             // step 3
//             ListNode *last = nullptr;
//             while (curr != next) {
//                 ListNode *temp = curr->next;
//                 curr->next = last;
//                 last = curr;
//                 curr = temp;
//             }
//         }
//         prev->next = curr;
//         return dummy->next;
//     }
// };

// Solution 2
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *dummy = new ListNode();
        ListNode *curr=head, *next=head;
        pair<ListNode*, ListNode*> reverseResult{nullptr, dummy};
        while (next != nullptr) {
            // 判断剩余结点数是否大于等于k
            int cnt=0;
            while (cnt<k && next != nullptr) {
                cnt++;
                next = next->next;
            }
            if (cnt != k) {
                break;
            }
            // 使用helper翻转k个结点，返回值为翻转后链表的头尾结点
            pair<ListNode*, ListNode*> newReverseResult = this->reverseSingleGroup(curr, k);
            // 将上一组的尾结点指向当前组的头结点
            reverseResult.second->next = newReverseResult.first;
            reverseResult = newReverseResult;
            curr = next;
        }
        reverseResult.second->next = curr;
        return dummy->next;
    }

private:
    pair<ListNode*, ListNode*> reverseSingleGroup(ListNode *head, int k) {
        ListNode *prev=nullptr, *curr=head;
        for (int i=0; i<k; ++i) {
            ListNode *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return pair<ListNode*, ListNode*>(prev, head);
    }
};

int main() {
    auto printList = [](ListNode *node){while (node!=nullptr){cout << node->val << endl; node=node->next;}};
    Solution s;
    ListNode *myList = new ListNode(1, new ListNode(2, new ListNode(3)));
    ListNode *retList = s.reverseKGroup(myList, 1);
    printList(retList);
    retList = s.reverseKGroup(myList, 2);
    printList(retList);
    cout << "-----------------" << endl;
    myList = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    retList = s.reverseKGroup(myList, 1);
    printList(retList);
    retList = s.reverseKGroup(myList, 3);
    printList(retList);
}