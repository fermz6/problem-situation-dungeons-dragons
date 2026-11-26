/*
Description: Stack header, declaration of functions
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#pragma once

template <typename T>
class Stack{
private:
    class Node{
        public:
        Node(T nData);
        T     data;
        Node    *next;
    };
    Node *top;

public:
    Stack();
    ~Stack();

    bool push(T data);
    bool pop();
    T* getTop();
    bool isEmpty();
    void releaseData();

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
};

#include "Stack.tpp"