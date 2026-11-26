/*
Description: Graph implementation, using BSF that is connected to the logic of queue and stack
Authors:
    Fernanda Magaña Zapata A01663341
    Vanessa Jacqueline Troncoso Ortega A01663244
Date: November 2026
*/

#include "Graph.h"
#include <fstream>
#include <sstream>

using namespace std;

Graph::Edge::Edge(unsigned int value) {
    target = value;
    weight = 1;
}

Graph::Graph(){
    vertices = nullptr;
    size = 0;
    visited = nullptr;
    previous = nullptr;
}

Graph::~Graph(){
    erase();
}

bool Graph::createGraph(unsigned int nSize){
    if(nSize == 0)
        return false;
    
    erase(); // Avoid collisions if called twice

    // If vertices could not be created return error
    vertices = new(nothrow) Vertex[nSize];
    if(!vertices)
        return false;
    
    visited = new(nothrow) bool[nSize];
    if(!visited){
        erase(); // Since vertices were already created
        return false;
    }

    previous = new(nothrow) unsigned int[nSize];
    if(!previous){
        erase(); // Vertices and visited already created
        return false;
    }

    size = nSize;
    resetArrays();
    return true;
}

// PREGUNTRALE A ARTEMIO SI ACEPTA DUPLICADOS !!!!!!!!!!
bool Graph::insertEdge(unsigned int from, unsigned int to){
    if(from >= size || to >= size)
        return false;
    
    Edge edge(to);
    if(vertices[from].edges.find(edge)) // Compares the target
        return false;
        
    return vertices[from].edges.insert(edge);
}

bool Graph::removeEdge(unsigned int from, unsigned int to){
    if(from >= size || to >= size)
        return false;
    
    Edge edge(to);
    return vertices[from].edges.remove(edge);
}

void Graph::erase(){
    delete [] vertices;
    delete [] visited;
    delete [] previous;
    vertices = nullptr;
    visited = nullptr;
    previous = nullptr;
    size = 0;
}

void Graph::resetArrays(){
    if(!visited || !previous)
        return;
    
    for(unsigned int i = 0; i < size; i++){
        visited[i] = false;
        previous[i] = NONE; // No previous
    }
}

unsigned int Graph::getSize(){
    return size;
}

// loads filename and returns whether the map was loaded successfully
bool Graph::loadFile(const std::string &filename) {
    ifstream file;
    file.open(filename);

    string line = "";

    if (!file.is_open()) {
        cout << "Could not open " << filename << '\n';
        return false;
    }
    
    if (!getline(file, line) || line != "Graph") {
        cout << "Missing or Invalid header\n";
        return false;
    }
    
    if (!getline(file, line)) {
        cout << "No number of vertices\n";
        return false;
    }
    
    // read the vertex count from the second line
    int nSize = 0;
    stringstream readValue(line);

    if (!(readValue >> nSize) || nSize <= 0) {
        cout << "Invalid vertex count\n";
        return false;
    }

    // allocate the vertices and the arrays used by the graph
    if (!createGraph(nSize)) {
        cout << "Could not create the graph\n";
        erase();
        return false;
    }

    // each line contains the destinations of one vertex
    for (unsigned int from = 0; from < size; from++) {
        if (!getline(file, line)) {
            // add three because vertex zero starts on file line three
            cout << "missing line " << from + 3 << '\n';
            return false;
        }

        // read destinations from this line without entering the next one
        stringstream readValue(line);
        int to = 0;

        // insertEdge checks the vertex range and rejects repeated edges
        while (readValue >> to) {
            if (to < 0 || !insertEdge(from, to)) {
                cout << "Invalid value or failed insertion on line " << from + 3 << '\n';
                return false;
            }
        }
    }

    file.close();
    return true;
}

// Help visit all elements in a graph, not necessary a route
bool Graph::BFS(unsigned int start){
    if(start>=size)
        return false;
    
    resetArrays();
    Queue<unsigned int> queue;
    if(!queue.enqueue(start))
        return false;
    visited[start] = true;

    std::cout << "BFS from " << start << ":";
    while(!queue.isEmpty()){
        unsigned int vertex = *queue.getFront();
        if(!queue.dequeue())
            return false;
        std::cout << " " << vertex;

        for(const Edge &edge : vertices[vertex].edges){
            if(!visited[edge.target]){
                visited[edge.target] = true;
                if(!queue.enqueue(edge.target))
                    return false;
            }
        }
    }
    std::cout << "\n";
    return true;
}

// Uses queue to keep a previous for every vertex and stop once end has been marked
bool Graph::BFSPath(unsigned int start, unsigned int end, DoublyLinkedList<unsigned int> &path){
    if(start >= size || end >= size)
        return false;
    
    resetArrays();
    Queue<unsigned int> queue;
    if(!queue.enqueue(start))
        return false;
    visited[start] = true;

    while(!queue.isEmpty() && !visited[end]){
        unsigned int vertex = *queue.getFront();
        if(!queue.dequeue())
            return false;

        for(const Edge &edge : vertices[vertex].edges){
            if(!visited[edge.target]) {
                visited[edge.target] = true;
                previous[edge.target] = vertex;
                if(!queue.enqueue(edge.target))
                    return false;
            }
        }
    }
    return buildPath(start, end, path);
}

// Rebuilds the route from end back to start with the stack
bool Graph::buildPath(unsigned int start, unsigned int end, DoublyLinkedList<unsigned int> &path) const {
    path.clear();
    if(end != start && previous[end] == NONE) // indicates that end was not reached
        return false;
    
    Stack<unsigned int> stack;
    for(unsigned int vertex = end; vertex != NONE; vertex = previous[vertex])
        if(!stack.push(vertex))
            return false;
    
    while(!stack.isEmpty()){
        if(!path.insert(*stack.getTop()))
            return false;
        stack.pop();
    }
    return true;
}