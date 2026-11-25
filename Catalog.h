/*
Description: Catalog class implementation
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#pragma once

#include <string>
#include "Monster.h"
#include "HashTable.h"

class Catalog {
private:
    HashTable<Monster> table;
    int count;

    bool isDigit(char value);
    bool isStringNumber(std::string text);
    bool isStringDecimal(std::string text);

public:
    Catalog();

    Catalog(const Catalog &other) = delete;
    Catalog &operator=(const Catalog &other) = delete;

    bool loadFromCSV(std::string filename);
    int getCount();
    Monster *getRandom();
    Monster *findByName(std::string name);
    void printStats();
};