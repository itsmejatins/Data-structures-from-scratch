#include <iostream>

using namespace std;

int adjSize = -1;
template <typename T>
class Node
{
public:
    Node *previous = nullptr, *next = nullptr;
    int row, col;
    T value;
  
    bool operator <(const Node &rhs) const
    {
        if(this->row != rhs.row)
            return this->row > rhs.row;
        else
            return this->col > rhs.col;
    }
    bool operator >(const Node &rhs) const
    {
        if(this->row != rhs.row)
            return this->row < rhs.row;
        else
            return this->col < rhs.col;
    }
    
    Node(int row, int col, T value)
    {
        this->row = row;
        this->col = col;
        this->value = value;
    }
    
    
};
template <typename T>
class PriorityQueue
{
private:
    T **elementData = nullptr;
    int maxSize = -1;
public:
    int lastIndex = -1;
private:
    void grow()
    {
        T **newElementData = new T*[2 * maxSize + 1];
        for(int i = 0; i <= lastIndex; i++)
        {
            newElementData[i] = elementData[i];
        }
        delete[] elementData;
        elementData = newElementData;
        maxSize = 2 * maxSize + 1;
    }
    int parent(int index)
    {
        return (index - 1) / 2;
    }
    
    int leftChild(int index)
    {
        if(2 * index + 1 <= lastIndex)
            return 2 * index + 1;
        else
            return -1;
    }
    int rightChild(int index)
    {
        if(2 * index + 2 <= lastIndex)
            return 2 * index + 2;
        else
            return -1;
    }
    void shiftUp(int cIndex)
    {
        while(cIndex > 0 && *elementData[cIndex] > *elementData[parent(cIndex)])
        {
            swap(elementData[cIndex], elementData[parent(cIndex)]);
            cIndex = parent(cIndex);
        }
    }
    
    void shiftDown(int pIndex)
    {
        while(true)
        {
            int indexToSwap{-1};
            if(leftChild(pIndex) != -1 && *elementData[pIndex] < *elementData[leftChild(pIndex)])
            {
                indexToSwap = leftChild(pIndex);
            }
            if(rightChild(pIndex) != -1 && *elementData[pIndex] < *elementData[rightChild(pIndex)])
            {
                if(indexToSwap == -1 || *elementData[rightChild(pIndex)] > *elementData[leftChild(pIndex)])
                    indexToSwap = rightChild(pIndex);
            }
            if(indexToSwap == -1)
                break;
            swap(elementData[pIndex], elementData[indexToSwap]);
            pIndex = indexToSwap;
        }
    }
public:
    void print()
    {
        for(int i = 0 ; i <= lastIndex; i++)
        {
            cout << "(" << elementData[i]->first << ", " << elementData[i]->second <<") " ;
        }
        cout << endl;
    }
    
public:
    void push(T *p)
    {
        if(lastIndex == maxSize-1)
            grow();
        elementData[++lastIndex] = p;
        shiftUp(lastIndex);
    }
    
    T* pop()
    {
        T *ret = elementData[0];
        elementData[0] = elementData[lastIndex--];
        shiftDown(0);
        return ret;
    }
    PriorityQueue(int size)
    {
        this->elementData = new T*[size];
        this->maxSize = size;
        this->lastIndex = -1;
    }
};

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
public:
    int rows{0}, cols{0}, size{0}, actualRows{0};
    
    void push_back(Node<T> *node)
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
    void remove(Node<T> *node)
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
    Node<T>* getFirstNode()
    {
        return head;
    }
    
    void rawPrint()
    {
        Node<T> *traverse = this->getFirstNode();
        while(traverse != nullptr)
        {
            cout << "(" << traverse->row << "," << traverse->col << "," << traverse->value  << ")" << endl;
            traverse = traverse->next;
        }
    }
    
    void matrixPrint()
    {
        
        Node<T> *traverse = head;
        for(int r = 0 ; r < rows; r++)
        {
            for(int c = 0; c < cols; c++)
            {
                if(traverse != nullptr && r == traverse->row && c == traverse->col)
                {
                    cout << traverse->value <<" ";
                    traverse = traverse->next;
                }
                else
                {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
        
    }
    
    void transpose()
    {
        if(this->actualRows == 0)
        {
            swap(this->rows, this->cols);
            return;
        }
        Node<T> *traverse = this->head;
        while(traverse != nullptr)
        {
            swap(traverse->row, traverse->col);
            traverse = traverse->next;
        }
        swap(this->rows, this->cols);
        PriorityQueue<Node<T>> *pq = new PriorityQueue<Node<T>>(this->size);
        while(getFirstNode() != nullptr)
        {
            Node<T> *first = getFirstNode();
            Node<T> *node = new Node<T>(first->row, first->col, first->value);
            pq->push(node);
            this->remove(first);
        }
        
        int count = pq->lastIndex + 1;
        for(int i = 0; i < count; i++)
        {
            Node<T> *node = pq->pop();
            this->push_back(node);
        }
        int id = head->row;
        this->actualRows = 1;
        traverse = head->next;
        while (traverse != nullptr)
        {
            if(traverse->row != id)
            {
                this->actualRows++;
                id = traverse->row;
            }
            traverse = traverse->next;
        }
        
    }
    
    static DoublyLinkedList* makeMatrix()
    {
        int rows{}, cols{};
       cout << "Enter number of rows: ";
        cin >> rows;
       cout << "Enter number of columns: ";
        cin >> cols;
        if(rows == 0 || cols == 0)
        {
            cout << "Matrix cannot have 0 length dimension, exiting" << endl;
            exit(1);
        }
        DoublyLinkedList *matrix = new DoublyLinkedList;
        matrix->rows = rows; matrix->cols = cols;
       cout << "Enter columns in row major order" << endl;
        for(int r = 0 ; r < rows; r++)
        {
            bool elementAdded = false;
            for(int c = 0; c < cols; c++)
            {
                int val{}; cin >> val;
                if(val != 0)
                {
                    Node<T> *node = new Node<T>(r, c, val);
                    matrix->push_back(node);
                    elementAdded = true;
                }
            }
            if(elementAdded)
            {
                matrix->actualRows++;
            }
        }
//        matrix->matrixPrint();
        return matrix;
    }
    
    static void additionUsingLinkedList()
    {
        DoublyLinkedList *m1 = makeMatrix();
        DoublyLinkedList *m2 = makeMatrix();
        
        if(m1->rows != m2->rows || m1->cols != m2->cols)
        {
            cout << "Incorrect dimensions for matrix addition, exiting...\n";
            exit(1);
        }
        if(m1->actualRows == 0)
        {
            m2->matrixPrint();
            return;
        }
        if(m2->actualRows == 0)
        {
            m1->matrixPrint();
            return;
        }
        
        DoublyLinkedList *addedM = new DoublyLinkedList;
        addedM->rows = m1->rows; addedM->cols = m1->cols;
        
        Node<T> *n1 = m1->getFirstNode(); Node<T> *n2 = m2->getFirstNode();
        while(n1 != nullptr || n2 != nullptr)
        {
            // remember that n1, n2 point to dynamically created objects on heap, not to some local variables
            if(n1 != nullptr && n2 != nullptr && n1->row == n2->row && n1->col == n2->col)
            {
                Node<T> *node = new Node<T>(n1->row, n1->col, n1->value + n2->value);
                addedM->push_back(node);
                n1 = n1->next; n2 = n2->next;
            }
            else if(n1 == nullptr)
            {
                Node<T> *node = new Node<T>(n2->row, n2->col, n2->value);
                addedM->push_back(node);
                n2 = n2->next;
            }
            else if(n2 == nullptr)
            {
                Node<T> *node = new Node<T>(n1->row, n1->col, n1->value);
                addedM->push_back(node);
                n1 = n1->next;
            }
            else // both nodes are not null and they dont represent the corresponding elements aat same position
            {
                if(n1->row < n2->row)
                {
                    Node<T> *node = new Node<T>(n1->row, n1->col, n1->value);
                    addedM->push_back(node);
                    n1 = n1->next;
                }
                else if(n2->row < n1->row)
                {
                    Node<T> *node = new Node<T>(n2->row, n2->col, n2->value);
                    addedM->push_back(node);
                    n2 = n2->next;
                }
                // now rows are same, columns must be different
                else if(n1->col < n2->col)
                {
                    Node<T> *node = new Node<T>(n1->row, n1->col, n1->value);
                    addedM->push_back(node);
                    n1 = n1->next;
                }
                else
                {
                    Node<T> *node = new Node<T>(n2->row, n2->col, n2->value);
                    addedM->push_back(node);
                    n2 = n2->next;
                }
            }
        }
        addedM->matrixPrint();
        cout << endl;
    }
    
    static void multiplicationUsingLinkedList()
    {
        DoublyLinkedList *m1 = makeMatrix();
        DoublyLinkedList *m2 = makeMatrix();
        DoublyLinkedList *res = new DoublyLinkedList;
        res->rows = m1->rows; res->cols = m2->cols;
        if(m1->actualRows == 0 || m2->actualRows == 0)
        {
            res->rows = m1->rows;
            res->cols = m2->cols;
            res->matrixPrint();
            return;
        }
        
        
        Node<T> *n1 = m1->getFirstNode();
        while(n1 != nullptr)
        {
            Node<T> *n2 = m2->getFirstNode();
            while(n2 != nullptr)
            {
                if(n1->col == n2->row)
                {
                    Node<T> *node = new Node<T>(n1->row, n2->col, n1->value * n2->value);
                    Node<T> *traverse = res->getFirstNode();
                    while(true)
                    {
                        if(traverse == nullptr)
                        {
                            res->push_back(node);
                            break;
                        }
                        if(traverse->row == node->row && traverse->col == node->col)
                        {
                            node->value = node->value + traverse->value;
                            res->remove(traverse);
                            res->push_back(node);
                            break;
                        }
                        traverse = traverse->next;
                    }
                }
                n2 = n2->next;
            }
            n1 = n1->next;
        }
        PriorityQueue<Node<T>> *pq = new PriorityQueue<Node<T>>(res->size);
        while(res->getFirstNode() != nullptr)
        {
            Node<T> *first = res->getFirstNode();
            Node<T> *node = new Node<T>(first->row, first->col, first->value);
            pq->push(node);
            res->remove(first);
        }
        int count = pq->lastIndex + 1;
        for(int i = 0; i < count; i++)
        {
            Node<T> *node = pq->pop();
            res->push_back(node);
        }
        int id = res->head->row;
        res->actualRows = 1;
        Node<T> *traverse = res->head->next;
        while (traverse != nullptr)
        {
            if(traverse->row != id)
            {
                res->actualRows++;
                id = traverse->row;
            }
            traverse = traverse->next;
        }
        res->matrixPrint();
    }

};

template <typename T>
class Array
{
    int currLength{-1}, maxLength{-1};
    int rows{-1}, cols{-1}, actRows{-1};
    Node<T> **elementData;
    
    void grow()
    {
        Node<T> **newElementData = new Node<T>*[2 * this->currLength];
        for(int i = 0 ; i < this->currLength; i++)
        {
            newElementData[i] = elementData[i];
        }
        delete elementData;
        elementData = newElementData;
        this->maxLength = 2 * this->maxLength;
    }
    
    class ArrayComparator
    {
    public:
        bool operator()(const Node<T>* lhs, const Node<T>* rhs)
        {
            if(lhs->row != rhs->row)
                return lhs->row < rhs->row;
            else
                return lhs->col < rhs->col;
        }
    };
public:

    bool push_back(Node<T> *node)
    {
        if(currLength == maxLength)
        {
            grow();
        }
        elementData[currLength++] = node;
        return true;
    }
    
    DoublyLinkedList<T>** createAdjList()
    {
        int id = this->elementData[0]->row;
        int actualRows = 1;
        for(int i = 1; i < this->currLength; i++)
        {
            if(elementData[i]->row != id)
            {
                actualRows++;
                id = elementData[i]->row;
            }
        }
        if(actualRows == 0)
            return nullptr;
        
        this->actRows = actualRows;
        DoublyLinkedList<T> **adjList = new DoublyLinkedList<T>*[actualRows];
        for(int i = 0 ; i < actualRows ;i++)
        {
            adjList[i] = new DoublyLinkedList<T>;
        }
        int i = 0, j = 1;
        id = this->elementData[0]->row;
        Node<T> *node = new Node<T>(elementData[0]->row, elementData[0]->col, elementData[0]->value);
        adjList[0]->push_back(node);
        while(j < currLength)
        {
            if(elementData[j]->row != id)
            {
                i++;
                id = elementData[j]->row;
            }
            node = new Node<T>(elementData[j]->row, elementData[j]->col, elementData[j]->value);
            adjList[i]->push_back(node);
            j++;
        }

        if(i != actualRows - 1)
        {
            cout << "Error while creating adjacency list\n";
            exit(1);
        }
        adjSize = actRows; // JUGAAD
        return adjList;
    }
    
    void matrixPrint()
    {
        bool hasRows = (actRows > 0);
        int i = 0;
        for(int r = 0 ; r < rows; r++)
        {
            for(int c = 0; c < cols; c++)
            {
                if(hasRows && (i < currLength && elementData[i]->row == r && elementData[i]->col == c))
                {
                    cout << elementData[i]->value << " ";
                    i++;
                }
                else
                    cout << "0 ";
            }
            cout << endl;
        }
    }
    
    static Array<T>* makeMatrix()
    {
        int rows{-1}, cols{-1};
       cout << "Enter number of rows :";
        cin >> rows;
       cout << "Enter number of cols :";
        cin >> cols;
        if(rows == 0 or cols == 0)
        {
            cout << "A matrix cannot have 0 as its dimension, exiting \n";
            exit(1);
        }
       cout << "Enter elements in row major order :\n";
        Array<T> *matrix = new Array<T>(rows * cols / 4 + 1);
        matrix->rows = rows; matrix->cols = cols, matrix->actRows = 0;
        bool elementAdded = false;
        for(int r = 0; r < rows; r++)
        {
            for(int c = 0; c < cols; c++)
            {
                T val{}; cin >> val;
                if(val != 0)
                {
                    Node<T>* node = new Node<T>(r, c, val);
                    elementAdded = true;
                    matrix->push_back(node);
                }
            }
            if(elementAdded)
            {
                matrix->actRows++;
                elementAdded = false;
            }
        }
        
        return matrix;
    }
    
    void transpose()
    {
        if(this->actRows == 0)
        {
            swap(rows, cols);
            return;
        }
        for(int i = 0 ; i <currLength; i++)
        {
            Node<T> *node = elementData[i];
            swap(node->row, node->col);
        }
        swap(rows, cols);
        ArrayComparator cmp;
        sort(elementData, elementData + currLength, cmp);
        int actualRows = 1 , id = elementData[0]->row;
        for(int i = 1; i < this->currLength; i++)
        {
            if(elementData[i]->row != id)
            {
                actualRows++;
                id = elementData[i]->row;
            }
        }
        this->actRows = actualRows;
    }
    
    void setActRows()
    {
        // element data should be sorted
        if(currLength == 0)
        {
            actRows = 0;
            return;
        }
        int id = elementData[0]->row; actRows = 1;
        for(int i = 1 ; i < currLength; i++)
        {
            if(elementData[i]->row != id)
            {
                actRows++;
                id = elementData[i]->row;
            }
        }
    }
    
    static void multiplication()
    {
        Array<T> *m1 = makeMatrix();
        Array<T> *m2 = makeMatrix();
        if(m1->cols != m2->rows)
        {
            cout << "Invalid matrix dimension for multiplication, exiting" << endl;
            exit(1);
        }
            
        Array<T> *res = new Array(max(m1->currLength, m2->currLength));
        if(m1->actRows == 0 || m2->actRows == 0)
        {
            res->rows = m1->rows;
            res->cols = m2->cols;
            res->matrixPrint();
            return;
        }
        m2->transpose();
        DoublyLinkedList<T> **adj1 = m1->createAdjList();
        int s1 = adjSize;
        DoublyLinkedList<T> **adj2 = m2->createAdjList();
        int s2 = adjSize;
        // dot product
        for(int i = 0 ; i < s1; i++)
        {
            for(int j = 0; j < s2; j++)
            {
                Node<T> *n1 = adj1[i]->getFirstNode();
                Node<T> *n2 = adj2[j]->getFirstNode();
                Node<T> *n1n2 = nullptr;
                while(n1 != nullptr && n2 != nullptr)
                {
                    if(n1->col == n2->col)
                    {
                        if(n1n2 == nullptr)
                            n1n2 = new Node<T>(n1->row, n2->row, 0);
                        n1n2->value += n1->value * n2->value;
                        n1 = n1->next;
                        n2 = n2->next;
                    }
                    else if(n1->col < n2->col)
                        n1 = n1->next;
                    else
                        n2 = n2->next;
                    
                }
                if(n1n2 != nullptr && n1n2->value != 0)
                {
                    res->push_back(n1n2);
                }
            }
        }
        res->rows = m1->rows; res->cols = m2->rows;
        res->matrixPrint();
        
    }
    
    static void addition()
    {
        Array<T> *m1 = makeMatrix();
        Array<T> *m2 = makeMatrix();
        if(m1->rows != m2->rows || m1->cols != m2->cols)
        {
            cout << "Invalid matrix dimensions for addition, exiting \n";
            exit(1);
        }
        if(m1->actRows == 0)
        {
            m2->matrixPrint();
            return;
        }
        if(m2->actRows == 0)
        {
            m1->matrixPrint();
            return;
        }
        // Now both matrice are not null
        Array<T> *res = new Array<T>(m1->currLength, m1->rows, m1->cols);
        int i = 0, j = 0;
        while(i < m1->currLength || j < m2->currLength)
        {
            if(i != m1->currLength && j != m2->currLength && m1->elementData[i]->row == m2->elementData[j]->row && m1->elementData[i]->col == m2->elementData[j]->col)
            {
                Node<T> *node = new Node<T>(m1->elementData[i]->row, m1->elementData[i]->col, m1->elementData[i]->value + m2->elementData[j]->value);
                res->push_back(node);
                i++;j++;
            }
            else if(i == m1->currLength)
            {
                 Node<T> *node = new Node<T>(m2->elementData[j]->row, m2->elementData[j]->col, m2->elementData[j]->value);
                res->push_back(node);
                j++;
            }
            else if(j == m2->currLength)
            {
                Node<T> *node = new Node<T>(m1->elementData[i]->row, m1->elementData[i]->col, m1->elementData[i]->value);
                res->push_back(node);
                i++;
            }
            else // both nodes are not null and they dont represent the corresponding elements at same position
            {
                if(m1->elementData[i]->row < m2->elementData[j]->row)
                {
                    Node<T> *node = new Node<T>(m1->elementData[i]->row, m1->elementData[i]->col, m1->elementData[i]->value);
                    res->push_back(node);
                    i++;
                }
                else if(m2->elementData[j]->row < m1->elementData[i]->row)
                {
                    Node<T> *node = new Node<T>(m2->elementData[j]->row, m2->elementData[j]->col, m2->elementData[j]->value);
                    res->push_back(node);
                    j++;
                }
                // now rows are same, columns must be different
                else if(m1->elementData[i]->col < m2->elementData[j]->col)
                {
                    Node<T> *node = new Node<T>(m1->elementData[i]->row, m1->elementData[i]->col, m1->elementData[i]->value);
                    res->push_back(node);
                    i++;
                }
                else
                {
                    Node<T> *node = new Node<T>(m2->elementData[j]->row, m2->elementData[j]->col, m2->elementData[j]->value);
                    res->push_back(node);
                    j++;
                }
            }
        }
        res->setActRows();
        res->matrixPrint();
        cout << endl;
        
    }
    
    Array(int maxLength)
    {
        elementData = new Node<T>*[maxLength];
        for(int i = 0 ; i < maxLength; i++)
            elementData[i] = nullptr;
        this->currLength = 0;
        this->maxLength = maxLength;
    }
    
    Array(int maxLength, int rows, int cols)
    {
        elementData = new Node<T>*[maxLength];
        for(int i = 0 ; i < maxLength; i++)
            elementData[i] = nullptr;
        this->currLength = 0;
        this->maxLength = maxLength;
        this->rows =rows;
        this->cols = cols;
    }
};


int main()
{
    int type{}, operation;
   cout << "enter type and operation" << endl;
    cin >> type; cin >> operation;
    
    if(type == 1)
    {
       cout << "Data structure : Array\n";
        if(operation == 1)
        {
           cout << "Operation selected : addition\n";
            Array<int>::addition();
        }
        else if(operation == 2)
        {
           cout << "Operation selected : transpose\n";
            Array<int> *matrix = Array<int>::makeMatrix();
            matrix->transpose();
            matrix->matrixPrint();
        }
        else if(operation == 3)
        {
           cout << "Operation selected : multiplication\n";
            Array<int>::multiplication();
        }
        
    }
    else if(type == 2)
    {
       cout << "Data structure : Linked List\n";
        if(operation == 1)
        {
           cout << "Operation selected : addition\n";
            DoublyLinkedList<int>::additionUsingLinkedList();
        }
        else if(operation == 2)
        {
           cout << "Operation selected : transpose\n";
            DoublyLinkedList<int> *matrix = DoublyLinkedList<int>::makeMatrix();
            matrix->transpose();
            
            matrix->matrixPrint();
        }
        else if(operation == 3)
        {
           cout << "Operation selected : multiplication\n";
            DoublyLinkedList<int>::multiplicationUsingLinkedList();
        }
        
    }



    
}


