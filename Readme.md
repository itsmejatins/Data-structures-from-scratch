# Data structures from scratch

# Manual Big Integer

In Java, the **`BigInteger`** class is a part of the **`java.math`** package and is used to handle arbitrary-precision integers. It allows the representation of integers of arbitrary size, limited only by the available memory of the system. This is particularly useful when dealing with very large numbers that cannot be accommodated by the standard primitive data types like **`int`** or **`long`**.

`ManualBigInteger.cpp` provides a custom implementation of big integer library, similar to the one available in Java in cpp. The library provides functionalities to store arbitrarily large integers and perform basic math operations as follows -

- `string addition(string &m, string &n)` → takes two numbers as input and returns their sum. Input and output format are in string.
- `string subtraction(string &m, string &n)` → takes two numbers as input and returns their difference. Input and output format are in string.
- `string multiplication(string &m, string &n)` → takes two numbers as input and returns their multiplication. Input and output format are in string.
- `string exponentiation(string &base, unsigned long long exponent)` → Calculates base ^ exponent. Here the base will be a big integer and the exponent will be a long.
- `string factorial(int n)` → It finds factorial of an integer n. Since the result of a factorial can be very large, the output is returned as a string.
- `string readInfix(string &input)` → This methods evaluates an infix expression.
    - Ex - Input: `32789123+99893271223x9203232392-4874223` ; Output: `919340989462382970316`
    - This method does not handles negative numbers present in intermediate results.
- `string gcd(string &m, string &n)` → It calculates gcd of two numbers using repeated subtraction.

# Manual deque implementation

- Deque is the same as dynamic arrays with the ability to resize itself automatically when an element is inserted or deleted, with their storage being handled automatically by the container
- They support insertion and Deletion from both ends in amortized constant time.
- Inserting and erasing in the middle is linear in time.

`Manual Deque.cpp` provides implementation of deque which satisfies the following performance requirements: (consider the data type as **T**) -

- **`deque()`** initialize a empty deque.Time complexity: O(1)
- **`deque(n, x)`** initialize a deque of length n with all values as x.
    - Time complexity: O(n)
- **`void push_back(x)`** append data x at the end.
    - Time complexity: O(1)
- **`void pop_back()`** erase data at the end.
    - Time complexity: O(1)
- **`void push_front(x)`** append data x at the beginning.
    - Time complexity: O(1)
- **`void pop_front()`** erase an element from the beginning.
    - Time complexity: O(1)
- **`T front()`** returns the first element(value) in the deque.
    - Time complexity: O(1)
- **`T back()`** returns the last element(value) in the deque.
    - Time complexity: O(1)
- **`T D[n]`** returns the nth element of the deque. The [] operator has be overloaded to perform this functionality.
    - Time complexity: O(1)
- **`bool empty()`** returns true if deque is empty else returns false.
    - Time complexity: O(1)
- **`int size()`** returns the current size of deque (i.e. the number of elements present in the deque).
    - Time complexity: O(1)
- **`void resize(x, d)`** - change the size dynamically to new size **x**.
    - Time complexity: O(n)
    - If the new size **x** is greater than the current size of the deque, then insert new elements with default value **d** at the end of the queue.
    - If the new size **x** is smaller than the current size, then keep **x** elements from the beginning of the deque.
- **`void clear()`** - remove all elements of deque.
    - Time complexity: O(1)

# Sparse matrix

- A matrix is generally represented using a 2D array. A sparse matrix is a matrix which has the majority of its elements set as 0. So using a conventional matrix representation scheme wastes a lot of memory. Here I come up with a representation of storing a sparse matrix in memory using -
    - array
    - linked list.
- I implemented an algorithm to perform addition, multiplication and transpose of the matrices. The addition and multiplication operations take two sparse matrices in conventional format (conventional format is the usual representation of a 2D matrix in row x column) and the return value should be the sum and product of the two matrices itself, respectively.
- The transpose operation take only one sparse matrix in conventional format and returns its transpose.
- Simply compile and run the `Sparse Matrix.cpp` file and follow the instructions on screen.

# Custom AVL tree

An AVL tree is a self-balancing binary search tree designed to maintain a balanced structure during insertion and deletion operations. The acronym "AVL" stands for the initials of its inventors, Adelson-Velsky and Landis. In an AVL tree, the heights of the two child subtrees of any node differ by at most one, ensuring that the tree remains approximately balanced.

Key features of AVL trees:

1. **Balance Factor:**
    - Each node in an AVL tree contains a balance factor, which is the difference between the heights of its left and right subtrees. The balance factor must be -1, 0, or 1 for every node in the tree.
2. **Self-Balancing Property:**
    - When an element is inserted or removed, the AVL tree automatically performs rotations (single or double) to restore the balance factor and maintain the logarithmic height of the tree.
3. **Logarithmic Height:**
    - The self-balancing property ensures that the height of the AVL tree remains logarithmic in the number of elements, providing efficient search, insertion, and deletion operations.
4. **Binary Search Tree Properties:**
    - In addition to the self-balancing feature, AVL trees maintain the binary search tree properties, where elements in the left subtree are smaller, and elements in the right subtree are larger than the node's value.

AVL trees are widely used in scenarios where the efficiency of search, insertion, and deletion operations is crucial. While the self-balancing mechanism adds overhead to these operations, it ensures that the tree remains well-balanced, preventing degradation of performance to O(log n) time complexity in the worst case.

`AVL.cpp` provides the implementation of the following operations. Generally AVL trees don’t handle duplicate values but this implementation of AVL trees handles duplicate values. 

| Operations  | Complexity | Method | Description |
| --- | --- | --- | --- |
| Insertion | O(log n) | void insert(T e) | Inserts an element e into the tree.  |
| Deletion | O(log n) | bool search(T e) | Searches for element with value e in tree and returns true if found, else false. |
| Search | O(log n) | void del (T e) | Deletes one occurrence of an element with value e from the tree. |
| Count occurrences of element | O(log n) | int count_occurrence(T e) | Counts number of elements with value e in the tree. |
| lower_bound | O(log n) | T lower_bound(T e) | Finds the smallest value ≥ e.  |
| upper_bound | O(log n) | T upper_bound(T e) | Finds that smallest value > e.  |
| closest element to some value | O(log n) | T closest_element(T e) | Find the node whose value is closest to e. |
| k-th largest element | O(log n) | T kth_largest(int k) | Finds the kth largest element in the tree. Takes into consideration that elements with duplicate values can be present in the tree. |
| count the number of elements in the tree whose values fall into a given range.  | O(log n) | int count_range(T e1, T e2) | Finds number of elements (including duplicates) whose value lies in the inclusive range of e1 - e2.  |
| print | O(n) | void print() | Prints in-order and pre-order traversal of the tree.  |

# Cache

## LRU cache

- An LRU (Least Recently Used) cache is a data structure that maintains a limited number of items and evicts the least recently used item when the maximum capacity is reached.
- Each time an item is accessed or modified, it is moved to the front of the cache to signify its recent use. When the cache reaches its capacity, the item at the end (least recently used) is removed to accommodate new entries.
- LRU caching is effective in scenarios where recently used items are more likely to be used again, optimizing performance by keeping frequently accessed data in a fast-accessible cache.
- Here I implement an LRU cache using doubly linked list and hashmap in `LRU.cpp`.

## LFU cache

- An LFU (Least Frequently Used) cache is a type of cache that evicts the least frequently used items when the cache reaches its capacity.
- Each time an item is accessed, its frequency count is increased. When the cache is full, the item with the lowest frequency count is removed. This ensures that items accessed less frequently are evicted first.
- LFU caching is useful in scenarios where the frequency of access, rather than recency, is a better indicator of an item's importance. It is effective in scenarios where some items are accessed more frequently than others.
- Here I implement an LFU cache using hashmaps and doubly linked lists in `LFU.cpp`.

# Unordered map

- An unordered map is a container in C++ that stores key-value pairs in an unordered manner. It provides constant-time average complexity for search, insertion, and deletion operations.
- It uses a hash table to organize elements, allowing for quick access to values based on their keys. The order of elements is not guaranteed, making it suitable for scenarios where the order of insertion is not important.
- Offers fast average-case performance for common operations and is well-suited for scenarios where the ordering of elements is not critical.
- `**UnorderedMap.cpp**` provides a custom implementation of a generic unordered map in cpp. It supports following functions -
    - **`insert(key, value)`** - insert the key-value pair. If the key already exists, update the value corresponding to the given key.
    - **`erase(key)`** – erase if the key is present otherwise do nothing.
    - **`find(key)`** – returns true if the key exists otherwise returns false.
    - `**map[key]**` – returns the value mapped to the key. If the key does not exist, return the default value of the datatype as the mapped value to the key.
- To run the program, compile and run `UnorderedMap.cpp` and provide input as follows -
    - First Line will contain a single integer **q** denoting the number of queries.
    - The next lines for each query follow the following pattern:
        - The first line will contain a single integer denoting the type of operation. [1 -> insert, 2 -> erase, 3 -> find, 4 -> map]
        - The second line will contain inputs based on the type of operation.
            - Type 1: 2 strings denoting the key, and value to be inserted respectively.
            - Type 2: 1 string denoting the key to be erased.
            - Type 3: 1 string denoting the key to be found.
            - Type 4: 1 string denoting the key on which operation must be applied.
- The output format is as follows -
    - Type 1: print nothing.
    - Type 2: print nothing.
    - Type 3: 1 if your output is true, 0 if your output is false.
    - Type 4: print the value associated with the key.