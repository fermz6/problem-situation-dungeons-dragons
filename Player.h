/*
Description: Player class header
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#pragma once

#include "Monster.h"
#include "DoublyLinkedList.h"

class Player {
private:
    std::string name;
    std::string race;
    int hp;
    int mp;
    DoublyLinkedList<Monster*> defeated;

public:
    Player(std::string name, std::string race);

    Player(const Player &other) = delete;
    Player &operator=(const Player &other) = delete;

    std::string getName();
    std::string getRace();
    int getHP();
    int getMP();

    void setMP(int value);
    bool addMonster(Monster *monster);
    void print();
};