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
    routePosition = 0;
}


bool Dungeon::loadMap(const std::string &filename){
    return map.loadFile(filename);
}

unsigned int Dungeon::getMapSize(){
    return map.getSize();
}

// create the rooms and insert monsters, if space in map
bool Dungeon::createRoom(const Monster &monster){
    if (rooms.size() >= map.getSize()) {
        return false;
    }

    Room room(monster);
    return rooms.insertAtEnd(room);
}

// obtain the value inside a specific room
Room* Dungeon::getRoom(int position){
    Room *target = rooms.getAt(position);
    return target;
}

// print the rooms
void Dungeon::printRooms(){
    for (int i = 0; i < rooms.countElements(); i++) {
        Room *room = rooms.getAt(i);

        if (room != nullptr) {
            cout << "Room " << i << ": " << *room << '\n';
        }
    }
}