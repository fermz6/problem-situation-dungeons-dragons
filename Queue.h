/*
Description: Queue header, declaration of fundamental functions
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#pragma once

template <typename T>
class Queue{
private:
    class Node{
    public:
        Node(T nData);
        T data;
        Node *next;
    };

    Node *front;
    Node *rear;
public:
    Queue();
    ~Queue();

    bool enqueue(T data);
    bool dequeue();
    T& getFront();
    bool isEmpty();
    void releaseData();

     // Prevent copying
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};

#include "Queue.tpp"