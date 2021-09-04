/*
Solution 1: 哈希表+双向链表
Solution 1.1: (TODO)使用STL的list实现双向链表
https://leetcode.com/problems/lru-cache/discuss/45912/Clean-Short-Standard-C%2B%2B-solution-NOT-writing-C-in-C%2B%2B-like-all-other-lengthy-ones
*/

#include<iostream>
#include<unordered_map>
#include<cassert>

using namespace std;

class DoubleLinkedList {
public:
    DoubleLinkedList(): key{0}, value{0}, front{nullptr}, back{nullptr}{};
    DoubleLinkedList(int key_, int value_): key{key_}, value{value_}, front{nullptr}, back{nullptr} {};
    int key;  // 将移出缓存的结点从dict中删除，需要根据链表结点找到dict元素，因此需要存储key
    int value;
    DoubleLinkedList* front;
    DoubleLinkedList* back;
};

class LRUCache {
public:
    LRUCache(int capacity) {
        cacheCapacity = capacity;
        cacheSize = 0;
        // Q: 到底需要几个dummy node？A: 两个，对应首尾，指向对方
        listFront = new DoubleLinkedList();
        listBack = new DoubleLinkedList();
        listFront->back = listBack;
        listBack->front = listFront;
    }
    
    int get(int key) {
        auto getIter = valueNodeMap.find(key);
        if (getIter == valueNodeMap.end()) {
            // otherwise return -1
            return -1;
        }else{
            // Return the value of the key if the key exists
            DoubleLinkedList *getNode = getIter->second;
            this->removeNode(getNode);
            this->appendBack(getNode);
            return getNode->value;
        }
    }
    
    void put(int key, int value) {
        auto getIter = valueNodeMap.find(key);
        // Update the value of the key if the key exists.
        if (getIter != valueNodeMap.end()) {
            DoubleLinkedList *getNode = getIter->second;
            getNode->value = value;
            this->removeNode(getNode);
            this->appendBack(getNode);
        }else{
            DoubleLinkedList *newNode = new DoubleLinkedList(key, value);
            // If the number of keys exceeds the capacity
            if (cacheSize == cacheCapacity) {
                // evict the least recently used key.
                DoubleLinkedList *deletedNode = listFront->back;
                this->removeNode(deletedNode);
                valueNodeMap.erase(deletedNode->key);
                delete deletedNode;
                cacheSize--;
            }
            this->appendBack(newNode);
            valueNodeMap.emplace(key, newNode);
            cacheSize++;
        }
    }

    void removeNode(DoubleLinkedList* node) {
        node->front->back = node->back;
        node->back->front = node->front;
        node->front = nullptr;
        node->back = nullptr;
    }

    void appendBack(DoubleLinkedList* node) {
        node->front = listBack->front;
        node->back = listBack;
        listBack->front->back = node;
        listBack->front = node;
    }
private:
    int cacheCapacity;
    int cacheSize;
    DoubleLinkedList* listFront;
    DoubleLinkedList* listBack;
    unordered_map<int, DoubleLinkedList*> valueNodeMap;
};

int main() {
    LRUCache lruCache(2);
    lruCache.put(1,1);
    lruCache.put(2,2);
    int ret = lruCache.get(1);
    assert(ret == 1);
    lruCache.put(3,3);
    ret = lruCache.get(2);
    assert(ret == -1);
    lruCache.put(4,4);
    ret = lruCache.get(1);
    assert(ret == -1);
    ret = lruCache.get(3);
    assert(ret == 3);
    ret = lruCache.get(4);
    assert(ret == 4);
    lruCache.put(4,2);  // 支持update已有元素
    ret = lruCache.get(4);
    assert(ret == 2);
}
