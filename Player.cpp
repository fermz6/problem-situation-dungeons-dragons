/*
Description: Player class implementation
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#include "Player.h"
#include <iostream>

using namespace std;

// create a player with 100 hp and 100 mp
Player::Player(string name, string race) {
    this->name = name;
    this->race = "human";

    if (race == "elf" || race == "human" || race == "dwarf") {
        this->race = race;
    }

    hp = 100;
    mp = 100;
}

// return the player name
string Player::getName() {
    return name;
}

// return the player race
string Player::getRace() {
    return race;
}

// return the hit points
int Player::getHP() {
    return hp;
}

// return the magic points
int Player::getMP() {
    return mp;
}

// set mp without exceeding 999
void Player::setMP(int value) {
    if (value > 999) {
        mp = 999;
    } else {
        mp = value;
    }
}

// store the monster pointer in name order
bool Player::addMonster(Monster *monster) {
    if (monster == nullptr) {
        return false;
    }

    int position = 0;
    int size = defeated.countElements();

    while (position < size) {
        Monster *other = *defeated.getAt(position);

        if (*monster < *other) {
            return defeated.insertAt(position, monster);
        }

        position++;
    }

    return defeated.insertAtEnd(monster);
}

// print the player and defeated monster names
void Player::print() {
    cout << "name: " << name << endl;
    cout << "race: " << race << endl;
    cout << "HP: " << hp << endl;
    cout << "MP: " << mp << endl;

    int size = defeated.countElements();

    if (size == 0) {
        cout << "defeated monsters: none" << endl;
    } else {
        cout << "defeated monsters:" << endl;

        for (int i = 0; i < size; i++) {
            Monster *monster = *defeated.getAt(i);
            cout << monster->getName() << endl;
        }
    }
}