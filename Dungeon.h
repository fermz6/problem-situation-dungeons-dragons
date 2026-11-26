/*
Description: Dungeon header, uses Doubly linked list to store the data creeated
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#pragma once
#include "DoublyLinkedList.h"
#include "Room.h"
#include "Catalog.h"
#include "Graph.h"

class Dungeon {
private:
    DoublyLinkedList<Room> rooms;
    Graph map;
    DoublyLinkedList<unsigned int> route;
    unsigned int routePosition;
public:
    Dungeon();

    // Prevent copying
    Dungeon(const Dungeon& other) = delete;
    Dungeon& operator=(const Dungeon& other) = delete;

    Room* getRoom(int position);
    bool loadMap(const std::string &filename);
    unsigned int getMapSize();
    bool createRoom(const Monster &monster);
    void printRooms();
    bool traceRoute(unsigned int start, unsigned int end);
    bool advanceRoute();
    Room* currentRouteRoom();
    void printRoute();
};