/*
Description: Stack template implementation
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#include "Stack.h"

template <typename T>
Stack<T>::Node::Node(T nData){
    data = nData;
    next = nullptr;
}

template <typename T>
Stack<T>::Stack(){
    top = nullptr;
}

template <typename T>
Stack<T>::~Stack(){
    releaseData();
}

template <typename T>
void Stack<T>::releaseData(){
    while(top){
        Node *temp = top->next;
        delete top;
        top = temp;
    }
}

template <typename T>
bool Stack<T>::push(T data){
    Node *newNode = new(std::nothrow) Node(data);

    if(!newNode){
       return false;
    }
    
    newNode->next = top;
    top = newNode;
    return true;
}

template <typename T>
bool Stack<T>::pop(){
    if(!top){
        return false; 
    }

    Node *temp = top;
    top = top->next;
    delete temp;
    return true;
}

template <typename T>
T* Stack<T>::getTop(){
    return top->data;
}

template <typename T>
bool Stack<T>::isEmpty(){
    if(!top)
        return true;
    return false;
}