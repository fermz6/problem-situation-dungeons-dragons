#pragma once

template <typename T>
class Queue{
public:
    Queue();
    ~Queue();

    class Node{
    public:
        Node(T nData);
        T data;
        Node *next;
    };

    bool enqueue(T data);
    bool dequeue();
    T& getFront();
    bool isEmpty();
    void releaseData();

private:
    Node *front;
    Node *rear;
};

#include "Queue.tpp"