/*
Description: Doubly Linked List header
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#pragma once

template <class T>
class DoublyLinkedList {
private:
    class Node {
    private:
        T data;
        Node *next;
        Node *prev;

        friend class DoublyLinkedList<T>;

    public:
        Node(T value);
    };

    Node *head;
    Node *tail;
    int count;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList &other) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &other) = delete;

    bool insertAtStart(T value);
    bool insertAtEnd(T value);
    bool insert(const T &data);
    bool insertAt(int position, T value);
    T *getAt(int position);
    T* find(const T &data);
    int countElements();
    unsigned int size();
    bool removeAt(int position);
    bool remove(const T &data);
    void print();
    void clearList();
    void clear();

    class Iterator {
    private:
        Node *current;

    public:
        // starts the iterator at the given node
        Iterator(Node *ptr) {
            current = ptr;
        }

        // returns the value stored at the current node
        T &operator*() const {
            return current->data;
        }

        // returns a pointer to the value stored at the current node
        T *operator->() const {
            return &(current->data);
        }

        // advances to the next node and returns this iterator
        Iterator &operator++() {
            if (current != nullptr) {
                current = current->next;
            }

            return *this;
        }

        // advances to the next node and returns the previous position
        Iterator operator++(int) {
            Iterator previous = *this;
            ++(*this);
            return previous;
        }

        // returns true if both iterators point to the same node
        bool operator==(const Iterator &other) const {
            return current == other.current;
        }

        // returns true if the iterators point to different nodes
        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }
    };

    // returns an iterator at the first node
    Iterator begin() {
        return Iterator(head);
    }

    // returns an iterator that marks the end of the list
    Iterator end() {
        return Iterator(nullptr);
    }
};

#include "DoublyLinkedList.tpp"
