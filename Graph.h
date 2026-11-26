/*
Description: Graph header, contains Edge and Vertex classes inside
Authors:
    Fernanda Magaña Zapata A01663341
    Vanessa Jacqueline Troncoso Ortega A01663244
Date: November 2026
*/

#pragma once

#include <string>
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Queue.h"

#define NONE UINT_MAX

// VOLVERLA TEMPLATE
class Graph{
private:
    class Edge{
    private:
        unsigned int target;
        unsigned int weight; // PREGUNTRALE A ARTEMIO QUE HACER CON EL WEIGHT!!!!
        friend class Graph;
    public:
        Edge(unsigned int value);
        bool operator==(const Edge &other) const{
            return target == other.target;
        }
    };

    class Vertex{
    public:
        DoublyLinkedList<Edge> edges; //Adjacency list
        friend class Graph;
    };

    Vertex *vertices; 
    unsigned int size;
    bool *visited;
    unsigned int *previous;

    void resetArrays();
    bool buildPath(unsigned int start, unsigned int end, DoublyLinkedList<unsigned int> &path) const;

public:
    Graph();
    ~Graph();

    //Prevent copying 
    Graph(const Graph &) = delete;
    Graph &operator=(const Graph &) = delete;

    bool createGraph(unsigned int nSize);
    bool insertEdge(unsigned int from, unsigned int to);
    bool removeEdge(unsigned int from, unsigned int to);
    void erase();
    bool loadFile(const std::string &filename);
    unsigned int getSize();
    bool BFS(unsigned int start);
    bool BFSPath(unsigned int start, unsigned int end, DoublyLinkedList<unsigned int> &path);
};
