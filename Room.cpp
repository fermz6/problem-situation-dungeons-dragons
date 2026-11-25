/*
Description: Room implementation.creates the logic for obtaining monsters and operator overloading
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#include "Room.h"
#include <iostream>

using namespace std;

// empty constructor
Room::Room(){
}

// parametrized constructor
Room::Room(const Monster& nMonster){
    this->monster = nMonster;
}

// Getter: Monster
Monster* Room::getMonster(){
    return &monster;
}

// Setter: monster
void Room::setMonster(const Monster& nMonster){
    this->monster = nMonster;
}

// Print the room monster with its attributes
ostream& operator <<(ostream& os, const Room& room){
    os << "Room with: " << room.monster.getName() << " [hp: " << room.monster.getHp() << ", ac: " << room.monster.getAc() << "]";
    return os;
}
