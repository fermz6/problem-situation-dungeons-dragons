/*
Description: Catalog class header
Version used:
    Author: Vanessa Jacqueline Troncoso Ortega
    ID: A01663244
Date: November 2026
*/

#include "Catalog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

// hashes a monster using only its name
unsigned int hashMonster(const Monster &monster) {
    string name = monster.getName();
    unsigned int hash = 0;

    for (string::size_type i = 0; i < name.size(); i++) {
        hash = hash * 31 + static_cast<unsigned char>(name[i]);
    }

    return hash;
}

// create an empty catalog
Catalog::Catalog() {
    count = 0;
}

// check if value is a digit
bool Catalog::isDigit(char value) {
    return value >= '0' && value <= '9';
}

// check if text contains only digits
bool Catalog::isStringNumber(string text) {
    if (text.empty()) {
        return false;
    }

    for (std::string::size_type i = 0; i < text.size(); i++) {
        if (!isDigit(text[i])) {
            return false;
        }
    }

    return true;
}

// check if text is a decimal number
bool Catalog::isStringDecimal(string text) {
    bool hasDecimalPoint = false;
    bool hasDigit = false;

    for (std::string::size_type i = 0; i < text.size(); i++) {
        if (isDigit(text[i])) {
            hasDigit = true;
        } else if (text[i] == '.' && !hasDecimalPoint) {
            hasDecimalPoint = true;
        } else {
            return false;
        }
    }

    return hasDigit;
}

// load monsters from the csv into the tree
bool Catalog::loadFromCSV(string filename) {
    ifstream file(filename);
    string line = "";
    int lineNumber = 1;

    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
        return false;
    }

    // skip the header
    if (!getline(file, line)) {
        cout << "Could not read the header" << endl;
        return false;
    }

    if (!table.createTable(11, hashMonster)) {
        cout << "Could not create the hash table" << endl;
        return false;
    }

    while (getline(file, line)) {
        lineNumber++;
        int commas = 0;

        for (std::string::size_type i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                commas++;
            }
        }

        if (commas != 6) {
            cout << "Invalid field count on line " << lineNumber << endl;
            return false;
        }

        Monster monster;
        string field = "";
        stringstream ss(line);

        for (int i = 0; i < 7; i++) {
            if (!getline(ss, field, ',')) {
                cout << "Missing field on line " << lineNumber << endl;
                return false;
            }

            switch (i) {
                case 0:
                    monster.setName(field);
                    break;

                case 1:
                    if (!isStringDecimal(field)) {
                        cout << "Invalid cr on line " << lineNumber << endl;
                        return false;
                    }

                    monster.setCr(stod(field));
                    break;

                case 2:
                    monster.setType(field);
                    break;

                case 3:
                    monster.setSize(field);
                    break;

                case 4:
                    if (!isStringNumber(field)) {
                        cout << "Invalid ac on line " << lineNumber << endl;
                        return false;
                    }

                    monster.setAc(stoi(field));
                    break;

                case 5:
                    if (!isStringNumber(field)) {
                        cout << "Invalid hp on line " << lineNumber << endl;
                        return false;
                    }

                    monster.setHp(stoi(field));
                    break;

                case 6:
                    monster.setAlign(field);
                    break;
            }
        }

        if (!table.insert(monster)) {
            cout << "Insertion failed on line " << lineNumber << endl;
            return false;
        }

        count++;
    }

    file.close();
    return true;
}

// return the number of loaded monsters
int Catalog::getCount() {
    return count;
}

// returns a random monster or nullptr if the catalog is empty
Monster *Catalog::getRandom() {
    if (count == 0) {
        return nullptr;
    }

    int position = rand() % count;
    return table.getAt(position);
}

// finds a stored monster by name or returns nullptr
Monster *Catalog::findByName(string name) {
    Monster key;
    key.setName(name);
    return table.find(key);
}

// prints the statistics of the catalog table
void Catalog::printStats() {
    table.printStats();
}