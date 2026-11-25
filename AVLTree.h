/*
Description: AVL Tree template header and iterator
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#pragma once

template <typename T>
class AVLTree {
private: 
    class Node {
    public:
        T data;
        int height;
        Node *left;
        Node *right;
        Node(T data);
    };
    Node *root;
    unsigned int count;
    
    bool insertRecursive(Node *&node, T data);
    bool removeRecursive(Node *&node, T data);
    void deleteRecursive(Node *&node);
    Node* replaceFromLeft(Node *&node);
    void printByLevelsRec(Node *node, int level);

    int getHeight(Node *node); 
    int checkBalance(Node *node); 
    void computeHeight(Node *node);
    void rebalance(Node *&node);
    Node* rotateRight(Node *node);
    Node* rotateLeft(Node *node);
    Node* doubleRotateRight(Node *node);
    Node* doubleRotateLeft(Node *node);

public: 
    AVLTree();
    ~AVLTree();

    bool insert(const T &data);
    T* find(const T &data);
    bool remove(const T &data);
    void clear();
    unsigned int size();
    int height();
    void printByLevels();

    // Prevent copying
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    // Iterator implementation IN-ORDER
    // It remembers the path from the root in a plain array
    class Iterator {
    public:
        Iterator() : top(0) {}
        
        explicit Iterator(Node *node) : top(0){
            pushLeft(node);
        }

        // ++i (pre-increment)
        Iterator& operator++(){
            if(top == 0)
                return *this;
            Node *node = path[--top]; //the current node leaves
            pushLeft(node->right); // then the smallest of it right subtree
            return *this;
        }

        // i++ (post-increment)
        Iterator operator++(int){
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return current() == other.current();
        }    
        bool operator !=(const Iterator& other) const {
            return current() != other.current();
        }

        T& operator*() const{
            return current()->data;
        }
        T* operator->() const {
            return &(current()->data);
        }

    private: 
        static const int MAX_HEIGHT = 64;
        Node* path[MAX_HEIGHT];
        int top;
        
        Node* current() const {
            return top ? path[top - 1] : nullptr;
        }
        void pushLeft(Node *n){
            while(n && top < MAX_HEIGHT){
                path[top++] = n;
                n = n->left;
            }
        }
    };

    Iterator begin() const {
        return Iterator(root);
    }
    
    Iterator end() const {
        return Iterator();
    }
};

#include "AVLTree.tpp"