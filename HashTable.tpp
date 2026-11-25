/*
Description: Hash Table implementation
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#include <new>
#include <iostream>

// starts with no buckets or hash function
template <class T>
HashTable<T>::HashTable() {
    buckets = nullptr;
    numBuckets = 0;
    numElements = 0;
    hash = nullptr;
}

// releases the array of buckets
template <class T>
HashTable<T>::~HashTable() {
    delete[] buckets;
}

// creates bucketCount buckets and saves hashFunction if allocation succeeds
template <class T>
bool HashTable<T>::createTable(unsigned int bucketCount, HashFunction hashFunction) {
    if (buckets != nullptr || bucketCount == 0 || hashFunction == nullptr) {
        return false;
    }

    buckets = new (std::nothrow) Bucket[bucketCount];

    if (buckets == nullptr) {
        return false;
    }

    numBuckets = bucketCount;
    hash = hashFunction;
    return true;
}

// returns the bucket index for value
template <class T>
unsigned int HashTable<T>::getIndex(const T &value) {
    return hash(value) % numBuckets;
}

// inserts a new value and grows the table when needed
template <class T>
bool HashTable<T>::insert(const T &value) {
    if (buckets == nullptr || find(value) != nullptr) {
        return false;
    }

    double nextLoad = (static_cast<double>(numElements) + 1) / numBuckets;

    if (nextLoad > 0.75) {
        unsigned int newSize = numBuckets * 2 + 1;

        while (!isPrime(newSize)) {
            newSize++;
        }

        if (!reHash(newSize)) {
            return false;
        }
    }

    if (!buckets[getIndex(value)].insert(value)) {
        return false;
    }

    numElements++;
    return true;
}

// returns a pointer to the stored value or nullptr if not found
template <class T>
T *HashTable<T>::find(const T &value) {
    if (buckets == nullptr) {
        return nullptr;
    }

    return buckets[getIndex(value)].find(value);
}

// removes value from its bucket and updates the element count
template <class T>
bool HashTable<T>::remove(const T &value) {
    if (buckets == nullptr) {
        return false;
    }

    unsigned int index = getIndex(value);

    if (!buckets[index].remove(value)) {
        return false;
    }

    numElements--;
    return true;
}

// returns the number of stored elements
template <class T>
unsigned int HashTable<T>::size() {
    return numElements;
}

// returns the number of buckets
template <class T>
unsigned int HashTable<T>::bucketCount() {
    return numBuckets;
}

// returns a pointer to the element at position or nullptr if it does not exist
template <class T>
T *HashTable<T>::getAt(unsigned int position) {
    if (position >= numElements) {
        return nullptr;
    }

    for (unsigned int i = 0; i < numBuckets; i++) {
        unsigned int currentSize = buckets[i].size();

        if (position < currentSize) {
            typename Bucket::Iterator it = buckets[i].begin();

            for (unsigned int j = 0; j < position; j++) {
                ++it;
            }

            return &(*it);
        }

        position -= currentSize;
    }

    return nullptr;
}

// prints the element count, bucket count, load factor and bucket sizes
template <class T>
void HashTable<T>::printStats() {
    unsigned int largestBucket = 0;
    unsigned int emptyBuckets = 0;
    double loadFactor = 0.0;

    for (unsigned int i = 0; i < numBuckets; i++) {
        unsigned int currentSize = buckets[i].size();

        if (currentSize == 0) {
            emptyBuckets++;
        }

        if (currentSize > largestBucket) {
            largestBucket = currentSize;
        }
    }

    if (numBuckets != 0) {
        loadFactor = static_cast<double>(numElements) / numBuckets;
    }

    std::cout << std::endl;
    std::cout << "Hash Table: " << std::endl;
    std::cout << "elements: " << numElements << std::endl;
    std::cout << "buckets: " << numBuckets << std::endl;
    std::cout << "load factor: " << loadFactor << std::endl;
    std::cout << "largest bucket: " << largestBucket << std::endl;
    std::cout << "empty buckets: " << emptyBuckets << std::endl;
    std::cout << std::endl;
}

// returns whether number is prime
template <class T>
bool HashTable<T>::isPrime(unsigned int number) {
    if (number < 2) {
        return false;
    }

    for (unsigned int divisor = 2; divisor <= number / divisor; divisor++) {
        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}

// moves the values to a new bucket array and keeps the old array on failure
template <class T>
bool HashTable<T>::reHash(unsigned int newSize) {
    Bucket *newBuckets = new (std::nothrow) Bucket[newSize];

    if (newBuckets == nullptr) {
        return false;
    }

    for (unsigned int i = 0; i < numBuckets; i++) {
        for (typename Bucket::Iterator it = buckets[i].begin();
            it != buckets[i].end(); ++it) {
            unsigned int index = hash(*it) % newSize;

            if (!newBuckets[index].insert(*it)) {
                delete[] newBuckets;
                return false;
            }
        }
    }

    delete[] buckets;
    buckets = newBuckets;
    numBuckets = newSize;
    return true;
}