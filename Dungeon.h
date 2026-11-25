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

class Dungeon {
private:
    DoublyLinkedList<Room> rooms;
public:
    Dungeon();
    bool createRoom(Monster &monster);
    Room* getRoom(int position);
    void print();

    Dungeon(const Dungeon& other) = delete;
    Dungeon& operator=(const Dungeon& other) = delete;
};