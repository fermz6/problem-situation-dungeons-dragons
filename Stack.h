#pragma once

template <typename T>
class Stack{
public:
    Stack();
    ~Stack();

    class Node{
        public:
        Node(T nData);
        T     data;
        Node    *next;
    };

    bool push(T data);
    bool pop();
    T& getTop();
    bool isEmpty();
    void releaseData();

private:
    Node *top;
};

#include "Stack.tpp"