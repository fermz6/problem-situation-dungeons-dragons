/*
Description: Room header, establishes the declaration of functions
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#pragma once
#include "Monster.h"
#include <iostream>

class Room{
private:
    Monster monster; // each room keeps its own copy of the catalogs monster
public:
    Room();
    Room(const Monster &nMonster);

    Monster* getMonster();
    void setMonster(const Monster &nMonster);

    friend std::ostream& operator <<(std::ostream& os, const Room& room);
};