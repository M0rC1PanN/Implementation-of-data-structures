# Implementation-of-data-structures 
This repo demonstrates my understanding of organisation and functional of basic data structures on C++ with tests.  
* __Dequeue-Queue-Stack.c++:__ includes 3 adapted structures with tests of implementation. 
..* Queue — a linear data structure that performs first in last out (FILO) rule. 
..* Stack — a linear data structure that performs first in first out (FIFO) rule. 
..* Double-ended queue — an abstract data type that combines queue and stack functional. 
* __BidirectionalList.c++__ includes a bidirectional linked list with iterators, tests to them.  

It is used in implementations of other data structures; the linked list doesn’t require space reallocation. Deletion and insertion takes constant time. But it doesn’t allow fast element search, O(n) complexity. 

Iterator is an interface that enables a programmer to go through a container. 
* __BinaryTree.c++__ includes a binary tree with tests. The tree data structure where each node has two children nodes. It enables fast sort and search of elements. 
* __Vector.c++__ Vector with tests. A resizable array with fast access and O(1) amortized time insert operation.  
* __HashMap.c++__ includes hash map with tests. The associative array abstract data structure provides constant time insertion, deletion and search on average.
