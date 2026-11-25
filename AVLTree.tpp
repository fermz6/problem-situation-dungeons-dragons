/*
Description: AVL Tree template implementation using recursive functions
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#include <iostream>
#include <new>
#include "AVLTree.h"

// Node constructor
template <typename T>
AVLTree<T>::Node::Node(T nData){
    data = nData;
    left = nullptr;
    right = nullptr;
    height = 0;
}

// AVL Tree default constructor
template <typename T>
AVLTree<T>::AVLTree(){
    root = nullptr;
    count = 0;
}

// AVL Tree destructor
template <typename T>
AVLTree<T>::~AVLTree(){
    clear();
}

// Delete all elements in the tree
template <typename T>
void AVLTree<T>::clear(){
    if(root){
        deleteRecursive(root);
    }
    count = 0;
}

// To know the height of a node
template <typename T>
int AVLTree<T>::getHeight(Node *node){
    if(!node)
        return -1; // Empty tree height is -1
    return node->height;
}

// Compute the difference between the childrens height
template <typename T>
void AVLTree<T>::computeHeight(Node *node){
    if(!node)
        return;

    int leftHeight = getHeight(node->left);
    int rightHeight= getHeight(node->right);

    if(leftHeight > rightHeight){
        node->height = leftHeight + 1;
    } 
    else {
        node->height = rightHeight + 1;
    }
}

// Update the height of the node after insert, delete or rotating
template <typename T>
int AVLTree<T>::checkBalance(Node *node){
    if(!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right); 
}

// Generic function to insert, calls insertRecursive
template <typename T>
bool AVLTree<T>::insert(const T &data){
    if(insertRecursive(root, data)){
        count++;
        return true;
    }
    return false;
}

// Logic for inserting nodes into an AVL Tree
template <typename T>
bool AVLTree<T>::insertRecursive(Node *&node, T data){
    if(!node){
        node = new(std::nothrow) Node(data);
        if(!node)
            return false;
        return true;
    }

    if(data < node->data){
        if(insertRecursive(node->left, data)){
            computeHeight(node);
            rebalance(node);
            return true;
        }
    }
    else if(data > node->data) {
        if(insertRecursive(node->right, data)){
            computeHeight(node);
            rebalance(node);
            return true;
        }
    }

    // Value is already in the tree, duplicates not allowed
    return false;
}

// Compares the address value with the target and return the result
template <typename T>
T* AVLTree<T>::find(const T &data){
    Node *current = root; 
    while(current){ 
        if(current->data == data){ 
            return &(current->data);
        }
        else if (current->data < data){
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    return nullptr;
}

// Obtain the full size of the tree
template <typename T>
unsigned int AVLTree<T>::size(){
    return count;
}

// Obtain the height of a node
template <typename T>
int AVLTree<T>::height(){
    return getHeight(root) + 1;
}

// Print the AVL Tree values, generic
template <typename T>
void AVLTree<T>::printByLevels(){
    printByLevelsRec(root, 0);
}

// Print the AVL Tree values, recursive
template <typename T>
void AVLTree<T>::printByLevelsRec(Node *node, int level){
    if(node == nullptr)
        return;

    printByLevelsRec(node->right, level +1);

    for(int i = 0; i < level; i++)
        std::cout << " "; // Add indentation spaces according to the level
    std::cout << node->data << "(" << node->height << ")" << std::endl;

    printByLevelsRec(node->left, level + 1);
}

// Remove a specific/only one node
template <typename T>
bool AVLTree<T>::remove(const T &data){
    if(removeRecursive(root, data)){
        count--;
        return true;
    }
    return false;
}

// logic implemented for preventing disbalance
template <typename T>
bool AVLTree<T>::removeRecursive(Node *&current, T data){
    if(!current)
        return false;

    if(data < current->data){
        if(!removeRecursive(current->left, data))
            return false;
    }
    else if(data > current->data){
        if(!removeRecursive(current->right, data))
            return false;
    }
    else{
        if(!current->left && !current->right){
            delete current;
            current = nullptr;
        }
        else if(!current->left){
            Node *temp = current;
            current = current->right;
            delete temp;
        }
        else if(!current->right) {
            Node *temp = current;
            current = current->left;
            delete temp;
        }
        else {
            // Two children
            Node *predecessor = replaceFromLeft(current->left); // highest of the left subtree
            current->data = predecessor->data; // Data from predecessor to current node
            if(!removeRecursive(current->left, predecessor->data))
                return false;
        }
    }    

    if(current) {
        computeHeight(current);
        rebalance(current);
    }
    return true;
}

// Delete until nothing is left in the tree
template <typename T>
void AVLTree<T>::deleteRecursive(Node *&node){
    if(!node)
        return;
    
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    
    delete node;
    node = nullptr;
}

// Computes the logic to connect the child
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::replaceFromLeft(Node *&node) {
    if(!node->right)
        return node;
    return replaceFromLeft(node->right);
}

// rotates to the left for balancing
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node *node){
    Node *nRoot = node->right;
    Node *temp = nRoot->left;

    nRoot->left = node;
    node->right = temp;

    computeHeight(node);
    computeHeight(nRoot);

    return nRoot;
}

// rotates to the right for balancing
template <typename T>
typename AVLTree<T>:: Node* AVLTree<T>::rotateRight(Node *node){
    Node *nRoot = node->left;
    Node *temp = nRoot->right;

    nRoot->right = node;
    node->left = temp;

    computeHeight(node);
    computeHeight(nRoot);

    return nRoot;
}

// rotates to the right and then left for balancing
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::doubleRotateLeft(Node *node){
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// rotates to the left and then right for balancing
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::doubleRotateRight(Node *node){
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// check the balance and do the appropiate rotations
template <typename T>
void AVLTree<T>::rebalance(Node *&node){
    int balance = checkBalance(node);

    //Rotation cases
    if(balance > 1){
        int leftChildBalance = checkBalance(node->left);

        if(leftChildBalance >= 0)
            node = rotateRight(node);
        else
            node = doubleRotateRight(node);
    }
    else if(balance < -1){
        int rightChildBalance = checkBalance(node->right);
        if(rightChildBalance <= 0)
            node = rotateLeft(node);
        else
            node = doubleRotateLeft(node);
    }
}