#include <iostream>
#include <map>
using namespace std;

class Node
{
public:
    Node *previous, *next;
    int value, key;
    
};

class DoublyLinkedList
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;
    int size{0};
public:
    void push_back(Node *node)
    {
        if(head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            node->previous = tail;
            node->next = nullptr;
            tail = node;
        }
        size++;
    }
    void remove(Node *node)
    {
        if(size == 0)
        {
            cout << "list empty "<<endl;
            return;
        }
        else if(size == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        // There are two cases when either previous node is null or next node is nullptr.
        else if(node == head)
        {
            head = head->next;
            delete node;
            head->previous = nullptr;
        }
        else if(node == tail)
        {
            tail = tail->previous;
            delete node;
            tail->next = nullptr;
        }
        // The general case where previous and next nodes are not null
        else
        {
            node->previous->next = node->next;
            node->next->previous = node->previous;
            delete node;
        }
        size --;
    }
    Node* getFirstNode()
    {
        return head;
    }
    
};

class LRUCache
{
    int size{0};
    map<int, Node*> cache;
    DoublyLinkedList lruList;
    
public:
    int get(int key)
    {
        if(cache.count(key) == 0)
        {
//            cout << "key not found" << endl;
            return -1;
        }
        Node *node = cache.at(key);
        int ret = node->value;
        lruList.remove(node);
        node = new Node;
        node->value = ret;
        node->key = key;
        lruList.push_back(node);
        cache.at(key) = node;
        return ret;
    }
    
    bool set(int key, int value)
    {
        if(size == 0)
            return false;
        if(cache.count(key) > 0)
        {
            Node *node = cache.at(key);
            lruList.remove(node);
            node = new Node;
            node->value = value;
            node->key = key;
            lruList.push_back(node);
            cache.at(key) = node;
            return true;
        }
        else // key not present
        {
            if(cache.size() < size) // cahce has empty space
            {
                Node *node = new Node;
                node->value = value;
                node->key = key;
                cache[key] = node;
                lruList.push_back(node);
                return true;
            }
            else if(cache.size() == size) // cache is full
            {
                Node *node = lruList.getFirstNode();
                cache.erase(node->key);
                lruList.remove(node);
                node = new Node;
                node->key = key;
                node->value = value;
                lruList.push_back(node);
                cache[key] = node;
            }
        }
        return false;
    }
    
    LRUCache(int capacity)
    {
        this->size = capacity;
    }
    
};

int main()
{
    // TESTING LOGIC
    int cap{};
    cin >> cap;
    LRUCache cache(cap);
    int q{};
    cin >> q;
    for(int i = 0 ; i < q; i++)
    {
        int op{}; cin >> op;
        if(op == 1)
        {
            int key{}; cin >> key;
            cout << cache.get(key);
        }
        else if(op == 2)
        {
            int key{}, val{};
            cin >> key; cin >> val;
            cache.set(key, val);
        }
    }
    return 0;
}
