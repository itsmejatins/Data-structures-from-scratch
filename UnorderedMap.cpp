#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

const int PRIME = 100003;

template <typename K, typename V>
class Node
{
    int hash{0};
    void hashcode(string k)
    {
        ostringstream oss;
        string hashString{};
        oss << k;
        hashString = oss.str();
        for(char c : hashString)
        {
            hash = (hash +  static_cast<int>(c)) % PRIME;
        }
    }
    void hashcode(int key)
    {
        hash = key % PRIME;
    }
    void hashcode(float key)
    {
        hash = static_cast<int>(key) % PRIME;
    }
    void hashcode(double key)
    {
        hash = hash = static_cast<int>(key) % PRIME;
    }
    void hashcode(long long key)
    {
        hash = hash = static_cast<long long>(key) % PRIME;
    }
public:
    K key;
    V value;
    
    Node<K, V> (K k, V v)
    {
        this->key = k;
        this->value = v;
        hashcode(k);
    }
};


template <typename K, typename V>
class UnorderedMap
{
    vector<Node<K, V>*> **bucket = new vector<Node<K,V>*>*[PRIME];
    int hashcode(string k)
    {
        int hash{};
        ostringstream oss;
        string hashString{};
        oss << k;
        hashString = oss.str();
        for(char c : hashString)
        {
            hash = (hash +  static_cast<int>(c)) % PRIME;
        }
        return hash;
    }
    
    int hashcode(int key)
    {
        return key % PRIME;
    }
    
    int hashcode(float key)
    {
        return static_cast<int>(key) % PRIME;
    }
    int hashcode(double key)
    {
       return static_cast<int>(key) % PRIME;
    }
    int hashcode(long long key)
    {
        return static_cast<long long>(key) % PRIME;
    }
    
public:
    int size{};
    void insert(K k, V v)
    {
        int hash = hashcode(k);
        if(bucket[hash] == nullptr)
        {
            vector<Node<K, V>*> *chain = new vector<Node<K, V>*>;
            Node<K, V> *node = new Node<K, V>(k, v);
            chain->push_back(node);
            bucket[hash] = chain;
            size++;
        }
        else
        {
            vector<Node<K, V>*> *chain = bucket[hash];
            bool keyPresent = false;
            for(Node<K, V> *node : *chain)
            {
                if(node->key == k)
                {
                    node->value = v;
                    keyPresent = true;
                    break;
                }
            }
            if(!keyPresent)
            {
                Node<K, V> *node = new Node<K, V>(k, v);
                chain->push_back(node);
                size++;
            }
        }
    }
    
    bool find(K k)
    {
        int hash = hashcode(k);
        if(bucket[hash] == nullptr)
            return false;
        vector<Node<K, V>*> *chain = bucket[hash];
        for(int i = 0 ; i < chain->size(); i++)
        {
            Node<K, V> *node = chain->at(i);
            if(node->key == k)
                return true;
        }
        return false;
    }
    
    V map(K k)
    {
        int hash = hashcode(k);
        if(bucket[hash] == nullptr)
            return *(new V());
        
        vector<Node<K, V>*> *chain = bucket[hash];
        for(Node<K, V> *node : *chain)
        {
            if(node->key == k)
                return node->value;
        }
        return *(new V());
    }
    
    void erase(K k)
    {
        int hash = hashcode(k);
        if(bucket[hash] == nullptr)
            return;
        
        vector<Node<K,V>*> *chain = bucket[hash];
        for(auto i = chain->begin(); i != chain->end(); i++)
        {
            if((*i)->key == k)
            {
                chain->erase(i);
                size--;
                i--;
                break;
            }
        }
        if(bucket[hash]->size() == 0)
            delete bucket[hash];
    }
    
    //    ~UnorderedMap()
    //    {
    //        for(int i = 0; i < size; i++)
    //        {
    //            if(bucket[i] != nullptr)
    //                delete bucket[i];
    //        }
    //        delete [] bucket;
    ////        delete this;
    //    }
    
};


template <typename K, typename V>
void getInput()
{
    UnorderedMap<K, V> map;
    int q{};
    cin >> q;
    for(int i = 0 ; i < q; i++)
    {
        int type{};
        cin >> type;
        if(type == 1)
        {
            K key{};
            V val{};
            cin >> key >> val;
            map.insert(key, val);
        }
        else if(type == 2)
        {
            K key{};
            cin >> key;
            map.erase(key);
        }
        else if(type == 3)
        {
            K key{};
            cin >> key;
            if(map.find(key))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if(type == 4)
        {
            K key{};
            cin >> key;
            cout << map.map(key) << endl;
        }
    }
}



int main()
{
    getInput<double, int>();
    return 0;
}
