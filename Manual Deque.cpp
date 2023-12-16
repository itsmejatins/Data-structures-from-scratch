
//  DSAP Assignment 1
//
//  Created by Jatin Sharma on 17/08/22.
//  Copyright © 2022 Jatin Sharma. All rights reserved.

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using namespace std;

template <typename T>
class DQ
{
private:
    T* elementData = nullptr;
    int f{-1}, r{-1}, currentSize{0}, maxSize = 0;
    
    void grow()
    {
        if(currentSize == maxSize)
        {
            T* newElementData = new T[maxSize * 2];
            int traverse{f}, i{0};
            while(traverse != r)
            {
                newElementData[i++] = elementData[traverse];
                traverse = (traverse + 1) % maxSize;
            }
            // at this point, front == rear, and i points to the first vacant position in the new deque.
            newElementData[i] = elementData[r];
            delete[] elementData;
            elementData = newElementData;
            maxSize *= 2;
            f = 0;
            r = i;
        }
    }
    
public:
    
    int size()
    {
        return this->currentSize;
    }
    
    void display()
    {
        if(currentSize == 0)
        {
            cout << "The deque is empty\n";
            return;
        }
        int i = f;
        while(i != r)
        {
            cout << elementData[i] << " ";
            i = (i + 1) % maxSize;
        }
        cout << elementData[r];
    }
    
    T operator[](int i)
    {
        if(currentSize == 0)
        {
            cout << "Deque is empty" << endl;
            return T();
        }
        if(i > currentSize -1)
        {
            cout << "Index out of bound" << endl;
            return T();
        }
        else
        {
            return elementData[(f + i) % currentSize];
        }
    }
    
    void push_back(T data)
    {
        grow(); // checking full deque condition
        if(f == -1 and r == -1)
        {
            f = r = 0;
            elementData[r] = data;
        }
        else
        {
            r = (r + 1) % maxSize;
            elementData[r] = data;
        }
        currentSize++;
    }
    // If size of deque becomes less than a threshold, then backing array will shrink
    T pop_back()
    {
        T t {};
        
        if(r == -1)
        {
            cout << "deque is empty" << endl;
            // modify code later to throw exception
            
        }
        
        else if(f == r) // deque has only one element
        {
            t = elementData[r];
            f = r = -1;
        }
        
        else
        {
            t = elementData[r];
            r--;
            if(r == -1)
            {
                r = maxSize - 1;
                // rear will always go back to the lastmost position of the array.
            }
        }
        currentSize--;
        return t;
    }
    
    void push_front(T x)
    {
        grow();
        // If deque is empty
        if(f == -1 && r == -1)
        {
            f = r = 0;
            elementData[f] = x;
        }
        else
        {
            // deque full condition has already been managed
            f = (f == 0) ? (maxSize - 1) : (f - 1);
            elementData[f] = x;
        }
        currentSize++;
    }
    
    T pop_front()
    {
        T t{};
        if((f == -1) && (r == -1))
        {
            cout << "deque is empty";
            // throw exception
        }
        else if (f == r)
        {
            t = elementData[f];
            f = r = -1;
        }
        else
        {
            t = elementData[f];
            f = (f + 1) % maxSize;
        }
        currentSize --;
        return t;
    }
    
    T front()
    {
        T t{};
        if((f == -1) && (r == -1))
        {
            cout << "deque is empty";
        }
        else
        {
            t = elementData[f];
        }
        return t;
    }
    
    T back()
    {
        T t{};
        if((f == -1) && (r == -1))
        {
            cout << "deque is empty";
        }
        else
        {
            t = elementData[r];
        }
        return t;
    }
    
    bool empty()
    {
        return currentSize == 0;
    }
    
    void resize(int x, T d)
    {
        if(x == currentSize)
        {
            return ;
        }
        else if(x > currentSize && x < maxSize)
        {
            int tempCount = x - currentSize;
            for(int i = 0 ; i < tempCount; i++)
            {
                push_back(d);
            }
        }
        
        else if(x > currentSize && x > maxSize)
        {
           
            T* newElementData = new T[2*x];
            int traverse = f, i = 0;
            while(traverse != r)
            {
                newElementData[i++] = elementData[traverse];
                traverse = (traverse + 1) % maxSize;
            }
            newElementData[i++] = elementData[traverse] ; // traverse == rear here and i points to the first vacant position, ie, r+1 after assignment
            delete[] elementData;
            elementData = newElementData;
            
            // Fill remaining positions with default value
            while(i < x) // i goes from currentSize to x-1
            {
                elementData[i++] = d;
            }
            currentSize = x;
            f = 0;
            r = currentSize - 1;
            maxSize = 2 * x;
        }
        else
        {
            r = (f + x - 1) % maxSize;
            currentSize = x;
        }
    }
    
    void clear()
    {
        delete[] elementData;
        elementData = new T[10];
        currentSize = 0;
        f = -1;
        r = -1;
        maxSize = 10;
        
        
    }
    // haNDLE N = 0
    DQ (int n, T x)
    {
        elementData = new T[n];
        for(int i = 0 ; i < n ; i++)
        {
            elementData[i] = x;
        }
        currentSize = maxSize = n;
        f = 0;
        r = maxSize - 1;
    }
    
    DQ()
    {
        elementData = new T[10];
        maxSize = 10;
    }
    
};


int main() {
    //NOTE - Spqecify template for DQ and val during compile time
    DQ<string> dq; // or Deque<float> DQ;
    string  val; // or float val;
    // 0 - QUIT
    // 1 - deque() ---- Provided through constructor
    // 2 - deque(n, x) -- Provided through constructor
    // 3 - push_back(x)
    // 4 - pop_back()
    // 5 - push_front(x)
    // 6 - pop_front()
    // 7 - front()
    // 8 - back()
    // 9 - empty()
    // 10 - size()
    // 11 - resize(n, x)
    // 12 - clear()
    // 13 - D[n]
    // 14 - display()
    int choice, flag = 1, n;
    while(flag) {
        cout << "-------------------------\n";
        cout << "choice: ";
        cin >> choice;
        switch(choice) {
            case 0:
                flag = 0;
                break;

            case 3:
                cin >> val;
                dq.push_back(val);
                break;
            case 4:
                dq.pop_back();
                break;
            case 5:
                cin >> val;
                dq.push_front(val);
                break;
            case 6:
                dq.pop_front();
                break;
            case 7:
                cout << dq.front() << endl;
                break;
            case 8:
                cout << dq.back() << endl;
                break;
            case 9:
                cout << ((dq.empty()) ? "true" : "false") << endl;
                break;
            case 10:
                cout << dq.size() << endl;
                break;
            case 11:
                cin >> n >> val;
                dq.resize(n, val);
                break;
            case 12:
                dq.clear();
                break;
            case 13:
                cin >> n;
                cout << dq[n] << endl;
                break;
            case 14:
                // For Debugging
                dq.display();
                break;
            default:
                cout << "Enter correct choice\n";
        }
    }
    
    return 0;
}



