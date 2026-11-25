/*
Description:
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#pragma once

#include "AVLTree.h"
#include "DoublyLinkedList.h"

template <class T>
class HashTable {
public:
    using HashFunction = unsigned int (*)(const T &);

    HashTable();
    ~HashTable();

    HashTable(const HashTable &) = delete;
    HashTable &operator=(const HashTable &) = delete;

    bool createTable(unsigned int bucketCount, HashFunction hashFunction);
    bool insert(const T &value);
    T *find(const T &value);
    bool remove(const T &value);
    unsigned int size();
    unsigned int bucketCount();
    T *getAt(unsigned int position);
    void printStats();

private:
    using Bucket = AVLTree<T>;

    Bucket *buckets;
    unsigned int numBuckets;
    unsigned int numElements;
    HashFunction hash;

    unsigned int getIndex(const T &value);
    bool isPrime(unsigned int number);
    bool reHash(unsigned int newSize);
};

#include "HashTable.tpp"