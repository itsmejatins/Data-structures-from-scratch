#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    Node *left = nullptr, *right = nullptr, *parent = nullptr;
    short whichChild{0}; // 0 = not a child, 1 = left child, 2 = right child
    int height = 0, nL{}, nR{};
    T value{};
    int freq{1};
    
    Node(){}
    Node(T value) {this->value = value;}
    Node(T value, Node *left, Node *right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }
    Node(T value, Node *parent)
    {
        this->value = value;
        this->parent = parent;
    }
    Node(Node *node) // copies only non-pointers
    {
        this->whichChild = node->whichChild;
        this->freq = node->freq;
        this->height = node->height;
        this->nL = node->nL;
        this->nR = node->nR;
        this->value = node->value;
    }
    
};

template <typename T>
class AVL
{
private:
    int size{0}, countHelper{};
    Node<T> *root = nullptr;
    T mod(T e)
    {
        if(e > 0)
            return e;
        else
            return e * -1.0;
    }
    Node<T>* find(Node<T> *root, T val) // returns the closest value, never null
    {
        if(root->value == val)
            return root;
        else if(val > root->value && root->right != nullptr)
            return find(root->right, val);
        else if(val < root->value && root->left != nullptr)
            return find(root->left, val);
        return root;
    }
    Node<T>* findNext(Node<T> *node)
    { // returns nullptr if node is the largest element
        if(size == 0 || size == 1)
            return nullptr;
        
        Node<T> *traverse = node;
        if(node->right != nullptr)
        {
            traverse = node->right;
            while(traverse->left != nullptr)
                traverse = traverse->left;
            return traverse;
        }
        else
        {
            while(traverse->parent != nullptr && traverse->parent->value < traverse->value)
                traverse = traverse->parent;
            
            return traverse->parent;
        }
    }
    Node<T>* findPrev(Node<T> *node)
    {   // returns nullptr if node is the smallest element
        if(size == 0 || size == 1)
            return nullptr;
        if(node->left != nullptr)
        {
            node = node->left;
            while(node->right != nullptr)
                node = node->right;
            return node;
        }
        else
        {
            while (node->parent != nullptr && node->parent->value > node->value)
                node = node->parent;
            return node->parent;
        }
    }
    void inOrder(Node<T> *root)
    {
        if(root == nullptr)
            return;
        inOrder(root->left);
        for(int i = 0; i < root->freq; i++)
        {
            cout << root->value << " ";
        }
        inOrder(root->right);
    }
    void preOrder(Node<T> *root)
    {
        if(root == nullptr)
            return;
        for(int i = 0 ; i < root->freq; i++)
        {
            cout << root->value << " ";
        }
        preOrder(root->left);
        preOrder(root->right);
    }
    int height(Node<T> *node)
    {
        if(node == nullptr)
            return -1;
        return node->height;
    }
    void adjustHeightAndCount(Node<T> *node)
    {
        if(node == nullptr)
            return;
        node->height = 1 + max(height(node->left), height(node->right));
        if(node->left == nullptr)
            node->nL = 0;
        else
            node->nL = node->left->freq + node->left->nL + node->left->nR;
        if(node->right == nullptr)
            node->nR = 0;
        else
            node->nR = node->right->freq + node->right->nL + node->right->nR;
    }
    Node<T>* findKthLargest(Node<T> *root, int k)
    {
        int lb = root->nR + 1;
        int ub = root->nR + 1 + root->freq - 1;
        if(k >= lb && k <= ub)
            return root;
        else if(k > ub)
            return findKthLargest(root->left, k - (root->nR + root->freq));
        else
            return findKthLargest(root->right, k);
    }
    void lessNodesCount(Node<T> *root, T k) // reset countHelper before calling the function
    {
        if(root == nullptr)
            return ;
        if(root->value < k)
        {
            countHelper += root->nL + root->freq;
            lessNodesCount(root->right, k);
        }
        else if(root->value > k)
            lessNodesCount(root->left, k);
        else
            countHelper += root->nL;
        
    }
    void greaterNodesCount(Node<T> *root, T k) // reset countHelper before calling the function
    {
        if(root == nullptr)
            return;
        if(root->value > k)
        {
            countHelper += root->freq + root->nR;
            greaterNodesCount(root->left, k);
        }
        else if(root->value < k)
            greaterNodesCount(root->right, k);
        else
            countHelper += root->nR;
    }
    void rotateRight(Node<T> *m)
    {
        Node<T> *n = m->parent;
        Node<T> *p = n->parent; // p can be null if n is root
        Node<T> *temp = m->right;
        m->right = n;
        m->parent = p;
        n->parent = m;
        n->left = temp;
        if(p != nullptr && n->whichChild == 1)
        {
            p->left = m;
            m->whichChild = 1;
        }
        if(p != nullptr && n->whichChild == 2)
        {
            p->right = m;
            m->whichChild = 2;
        }
        n->whichChild = 2;
        if(temp != nullptr)
        {
            temp->whichChild = 1;
            temp->parent = n;
        }
        
        // n becomes child of m. Need to balance height of n and all its ancestors
        Node<T> *traverse = n;
        while(traverse != nullptr)
        {
            adjustHeightAndCount(traverse);
            traverse = traverse->parent;
        }
        
        if(p == nullptr)
            root = m;
    }
    void rotateLeft(Node<T> *m)
    {
        Node<T> *n = m->parent;
        Node<T> *p = n->parent;
        Node<T> *temp = m->left;
        m->left = n;
        m->parent = p;
        n->parent = m;
        n->right = temp;
        if(p != nullptr && n->whichChild == 1)
        {
            p->left = m;
            m->whichChild = 1;
        }
        else if(p != nullptr && n->whichChild == 2)
        {
            p->right = m;
            m->whichChild = 2;
        }
        n->whichChild = 1;
        if(temp != nullptr)
        {
            temp->whichChild = 2;
            temp->parent = n;
        }
        Node<T> *traverse = n;
        while(traverse != nullptr)
        {
            adjustHeightAndCount(traverse);
            traverse = traverse->parent;
        }
        
        if(p == nullptr)
            root = m;
    }
    void rebalanceRight(Node<T> *node)
    {
        Node<T> *m = node->left;
        if(height(m->right) > height(m->left))
            rotateLeft(m->right);
        rotateRight(node->left);
    }
    void rebalanceLeft(Node<T> *node)
    {
        Node<T> *m = node->right;
        if(height(m->left) > height(m->right))
            rotateRight(m->left);
        rotateLeft(node->right);
    }
    void rebalance(Node<T> *node)
    {
        if(node == nullptr)
            return;
        Node<T> *parent = node->parent;
        if(height(node->left) > height(node->right) + 1)
            rebalanceRight(node);
        if(height(node->right) > height(node->left) + 1)
            rebalanceLeft(node);
        adjustHeightAndCount(node); // basically you need to do this only if no rotation happens because rotation automatically fixes height, modify code after testing.
        rebalance(parent);
    }
public:
    
    void insert(T e)
    {
        if(root == nullptr)
        {
            Node<T> *node = new Node<T>(e, nullptr);
            root = node;
        }
        else
        {
            Node<T> *node = find(root, e);
            if(node->value == e)
            {
                node->freq++;
                rebalance(node);
            }
            else if(e > node->value)
            {
                Node<T> *ins = new Node<T>(e, node);
                node->right = ins;
                ins->whichChild = 2;
                rebalance(ins);
            }
            else
            {
                Node<T> *ins = new Node<T>(e, node);
                node->left = ins;
                ins->whichChild = 1;
                rebalance(ins);
            }
        }
        size++;
    }
    bool search(T e)
    {
        Node<T> *node = find(root, e);
        return (node->value == e);
    }
    void del (T e)
    {
        if(!search(e)) return;
        Node<T> *node = find(root, e);
        if(node->freq > 1)
        {
            (node->freq)--;
            rebalance(node);
            return;
        }
        if(node->left == nullptr && node->right == nullptr) // either leaf node or single root node
        {
            if(node == root)
            {
                delete root;
                root = nullptr;
            }
            else
            {
                Node<T> *parent = node->parent;
                if(node->whichChild == 1)
                {
                    delete parent->left;
                    parent->left = nullptr;
                }
                else if(node->whichChild == 2)
                {
                    delete parent->right;
                    parent->right = nullptr;
                }
                rebalance(parent);
            }
        }
        else if(node->left != nullptr && node->right == nullptr)
        {
            if(node == root)
            {
                root = root->left;
                delete node;
            }
            else
            {
                Node<T> *parent = node->parent;
                if(node->whichChild == 1)
                {
                    parent->left = node->left;
                    delete node;
                }
                else if(node->whichChild == 2)
                {
                    parent->right = node->left;
                    delete node;
                }
                rebalance(parent);
            }
        }
        else if(node->right != nullptr && node->left == nullptr)
        {
            if(node == root)
            {
                root = root->right;
                delete node;
            }
            else
            {
                Node<T> *parent = node->parent;
                if(node->whichChild == 1)
                {
                    parent->left = node->right;
                    delete node;
                }
                else if(node->whichChild == 2)
                {
                    parent->right = node->right;
                    delete node;
                }
                rebalance(parent);
            }
        }
        else if(node->right != nullptr && node->left != nullptr)
        {
            Node<T> *next = findNext(node);
            Node<T> *parent = next->parent; // The old parent of node replacing *node
            Node<T> *temp = new Node<T>(next);
            next->freq = 1;
            del(next->value);
            node->value = temp->value;
            node->freq = temp->freq;
            rebalance(parent);
            delete temp;
        }
        size--;
    }
    int count_occurrence(T e)
    {
        Node<T> *node = find(root, e);
        if(node->value == e)
            return node->freq;
        return 0;
    }
    T lower_bound(T e)
    {
        Node<T> *node = find(root, e);
        if(node->value >= e)
            return node->value;
        else
        {
            node = findNext(node);
            if(node != nullptr)
                return node->value;
            else
                return *(new T());
        }
    }
    T upper_bound(T e)
    {
        Node<T> *node = find(root, e);
        if(node->value > e)
            return node->value;
        else
        {
            node = findNext(node);
            if(node != nullptr)
                return node->value;
            else
                return *(new T());
        }
    }
    T closest_element(T e)
    {
        Node<T> *node = find(root, e);
        if(node->value == e)
            return e;
        else if(node->value > e)
        {
            Node<T> *prev = findPrev(node);
            if(prev == nullptr)
                return node->value;
            T diff1 = e - prev->value;
            T diff2 = node->value - e;
            if(diff1 > diff2)
                return node->value;
            else
                return prev->value;
        }
        else
        {
            T diff1 = e - node->value;
            Node<T> *next = findNext(node);
            if(next == nullptr)
                return node->value;
            T diff2 = next->value - e;
            if(diff1 > diff2)
                return next->value;
            else
                return node->value;
        }
        
    }
    T kth_largest(int k)
    {
        if(k > size || k < 1)
            return *(new T());
        Node<T> *node = findKthLargest(root, k);
        return node->value;
    }
    int count_range(T e1, T e2)
    {
        if(e1 > e2)
            return 0;
        if(e1 == e2)
        {
            return count_occurrence(e1);
        }
        countHelper = 0;
        lessNodesCount(root, e1);
        int c1 = countHelper;
        countHelper = 0;
        greaterNodesCount(root, e2);
        int c2 = countHelper;
        countHelper = 0;
        return this->size - (c1 +c2);
    }
    void print()
    {
        if(root == nullptr)
        {
            cout <<"tree is empty" << endl;
            return;
        }
        cout << "Inorder :: ";
        inOrder(root);
        cout << endl;
        cout << "Preorder :: ";
        preOrder(root);
        cout << endl;
        
    }
};


int main()
{
    AVL<float> *avl = new AVL<float>();
    avl->insert(5);
    avl->insert(4);
    avl->insert(3);
    avl->insert(2);
    avl->insert(1);
    avl->insert(5);
    avl->insert(4);
    avl->insert(3);
    avl->insert(2);
    avl->insert(1);
    avl->del(4);
    avl->del(4);
    avl->insert(1.1);
    avl->print();
    
    cout << avl->count_range(1.22, 1.22) << " ";
    return 0;
}
