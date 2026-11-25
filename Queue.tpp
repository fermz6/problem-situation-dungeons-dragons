/*
Description: Queue template implementation
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#include "Queue.h"

template <typename T>
Queue<T>::Node::Node(T nData){
    data = nData;
    next = nullptr;
}

template <typename T>
Queue<T>::Queue(){
    front = nullptr;
    rear = nullptr;
}

template <typename T>
Queue<T>::~Queue(){
    releaseData();
}

template <typename T>
void Queue<T>::releaseData(){
    while(front){
        Node *temp = front->next;
        delete front;
        front = temp;
    }
    rear = nullptr;
}

template <typename T>
bool Queue<T>::enqueue(T data){
    Node *newNode = new(nothrow) Node(data);

    if(!newNode){
        return false;
    }

    // If queue is empty 
    if(!front){
        front = newNode;
        rear = newNode;
        return true;
    }

    rear->next = newNode;
    rear = newNode;
    return true;
}

template <typename T>
bool Queue<T>::dequeue(){
    if(!front){
        return false;
    }

    Node *temp = front;
    front = front->next;
    if(!front){ // If we have just erased the last number
        rear = nullptr;
    }
    delete temp;
    return true;
}

template <typename T>
T& Queue<T>::getFront(){
    return front->data;
}

template <typename T>
bool Queue<T>::isEmpty(){
    if(!front){
        return true;
    }
    return false;
}