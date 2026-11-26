/*
Description: Doubly Linked List implementation
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#include <iostream>
#include <new>

#include "DoublyLinkedList.h"
template <class T>
DoublyLinkedList<T>::Node::Node(T value) : data(value) {
    next = nullptr;
    prev = nullptr;
}

// create an empty list
template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// release all nodes
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clearList();
}

// insert value at the start
template <class T>
bool DoublyLinkedList<T>::insertAtStart(T value) {
    Node *newNode = new (std::nothrow) Node(value);

    if (newNode == nullptr) {
        return false;
    }

    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }

    head = newNode;
    count++;
    return true;
}

// insert value at the end
template <class T>
bool DoublyLinkedList<T>::insertAtEnd(T value) {
    Node *newNode = new (std::nothrow) Node(value);

    if (newNode == nullptr) {
        return false;
    }

    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode;
    }

    tail = newNode;
    count++;
    return true;
}

// inserts data at the end and returns whether it was added
template <class T>
bool DoublyLinkedList<T>::insert(const T &data) {
    return insertAtEnd(data);
}

// insert value at position
template <class T>
bool DoublyLinkedList<T>::insertAt(int position, T value) {
    if (position < 0 || position > count) {
        return false;
    }

    if (position == 0) {
        return insertAtStart(value);
    }

    if (position == count) {
        return insertAtEnd(value);
    }

    Node *current = head;

    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    Node *newNode = new (std::nothrow) Node(value);

    if (newNode == nullptr) {
        return false;
    }

    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    count++;

    return true;
}

// return a pointer to the data at position or nullptr if not found
template <class T>
T *DoublyLinkedList<T>::getAt(int position) {
    if (position < 0 || position >= count) {
        return nullptr;
    }

    Node *current = head;

    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    return &(current->data);
}

// searches for data and returns its address, or nullptr if not found
template <class T>
T *DoublyLinkedList<T>::find(const T &data) {

    Node *current = head;

    while (current != nullptr) {
        // compare the stored value with the desired value, if matched then return address
        if(current->data == data) {
            return &(current->data);
        }

        current = current->next;
    }

    return nullptr;
}

// removes the first match and returns whether it was removed
template <class T>
bool DoublyLinkedList<T>::remove(const T &data) {
    Node *current = head;
    int position = 0;

    while (current != nullptr) {
        if (current->data == data) {
            return removeAt(position);
        }

        current = current->next;
        position++;
    }

    return false;
}


// return the stored number of nodes
template <class T>
int DoublyLinkedList<T>::countElements() {
    return count;
}

template <class T>
unsigned int DoublyLinkedList<T>::size() {
    return count;
}

// remove the node at position and report whether it existed
template <class T>
bool DoublyLinkedList<T>::removeAt(int position) {
    if (position < 0 || position >= count) {
        return false;
    }

    Node *current = head;

    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }

    delete current;
    count--;
    return true;
}

// print each stored value in order using its stream operator
template <class T>
void DoublyLinkedList<T>::print() {
    Node *current = head;

    while (current != nullptr) {
        std::cout << current->data << '\n';
        current = current->next;
    }
}

// release all nodes and leave the list empty
template <class T>
void DoublyLinkedList<T>::clearList() {
    while (head != nullptr) {
        Node *tmp = head->next;
        delete head;
        head = tmp;
    }

    tail = nullptr;
    count = 0;
}

template <class T>
void DoublyLinkedList<T>::clear() {
    clearList();
}