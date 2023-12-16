#include <iostream>
#include <map>
using namespace std;

class Node
{
public:
    Node *previous, *next;
    int value, key, count;
    
    Node(int key, int value, int count)
    {
        this->key = key; this->value = value; this->count = count;
    }
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
    
    int getSize()
    {
        return this->size;
    }
    
};

class LFUCache
{
private:
    int size{0};
    map<int, Node*> cache;
    map<int, DoublyLinkedList*> fMap;
    
public:
    
    int get(int key)
    {
        if(cache.find(key) == cache.end())
            return -1;
        
        Node *node = cache.at(key);
        int ret = node->value;
        int c = node->count;
        fMap.at(c)->remove(node);
        if(fMap.at(c)->getSize() == 0)
        {
            delete fMap.at(c);
            fMap.erase(c);
        }
        if(fMap.find(c+1) == fMap.end()) // freq key does not exist, put a list at that location
        {
            DoublyLinkedList *list = new DoublyLinkedList;
            fMap[c+1] = list;
        }
        node = new Node(key, ret, c+1);
        fMap.at(c+1)->push_back(node);
        
        //Update cache with new address of that node for current key
        cache.at(key) = node;
        
        return ret;
    }
    
    bool set(int key, int value)
    {
        if(this->size == 0)
            return false;
        if(cache.find(key) != cache.end()) // update the existing key
        {
            Node *node = cache.at(key);
            int c = node->count;
            fMap.at(c)->remove(node);
            if(fMap.at(c)->getSize() == 0)
            {
                delete fMap.at(c);
                fMap.erase(c);
            }
            if(fMap.find(c+1) == fMap.end()) // freq key does not exist, put a list at that location
            {
                DoublyLinkedList *list = new DoublyLinkedList;
                fMap[c+1] = list;
            }
            node = new Node(key, value, c+1);
            fMap[c+1]->push_back(node);
            cache.at(key) = node;
        }
        else if(cache.size() < size) // space available
        {
            Node *node = new Node(key, value, 1);
            cache[key] = node;
            
            if(fMap.find(1) == fMap.end()) // freq key does not exist, put a list at that location
            {
                DoublyLinkedList *list = new DoublyLinkedList;
                fMap[1] = list;
            }
            fMap.at(1)->push_back(node);
        }
        else // cache full, need to remove items
        {
            DoublyLinkedList *list = fMap.begin()->second;
            Node *nodeToRemove = list->getFirstNode();
            int c = fMap.begin()->first;
            
            cache.erase(nodeToRemove->key);
            list->remove(nodeToRemove);
            nodeToRemove = nullptr;
            if(fMap.at(c)->getSize() == 0)
            {
                delete fMap.at(c);
                fMap.erase(c);
            }
            Node *node = new Node(key, value, 1);
            cache[key] = node;
            if(fMap.find(1) == fMap.end())
            {
                DoublyLinkedList * list = new DoublyLinkedList;
                fMap[1] = list;
            }
            fMap.at(1)->push_back(node);
        }
        return true;
    }
    
    LFUCache(int size = 0)
    {
        this->size = size;
    }
};

int main()
{
    // TESTING LOGIC
    int cap{};
    cin >> cap;
    LFUCache cache(cap);
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

