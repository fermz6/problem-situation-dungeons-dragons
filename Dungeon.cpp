/*
Description: Dungeon implementation, creates room with monsters
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#include "Dungeon.h"
#include <iostream>

using namespace std;

Dungeon::Dungeon(){
}

// create the rooms and insert monsters in order
bool Dungeon::createRoom(const Monster &monster){
    Room room(monster);
    if(!rooms.insertAtEnd(room))
        return false;

    return true;
}

// obtain the value inside a specific room
Room* Dungeon::getRoom(int position){
    Room *target = rooms.getAt(position);
    return target;
}

// print the rooms
void Dungeon::printRooms(){
    rooms.print();
}