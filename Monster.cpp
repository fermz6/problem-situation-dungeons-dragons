/*
Description: Monster implememtation, create constructors for monsters, getters, setters and operator overloading 
Version used:
    Author: Fernanda Magaña Zapata
    ID: A01663341
Date: November 2026
*/

#include "Monster.h"
using namespace std;
#include <iostream>

// default constructor
Monster::Monster(){
        this->name = "No name";
        this->cr = 0.0;
        this->type = "No type";
        this->size = "No size";
        this->ac = 0;
        this->hp = 0;
        this->align = "No align";
}

// initialized constructor
Monster::Monster(std::string name, double cr, std::string type, std::string size, int ac, int hp, std::string align){
        this->name = name;
        this->cr = cr;
        this->type = type;
        this->size = size;
        this->ac = ac;
        this->hp = hp;
        this->align = align;
}

// destructor
Monster::~Monster(){
}

// Getter: name 
string Monster::getName() const{
    return this->name;
}

// Setter: name 
void Monster::setName(string name){
    this->name = name;
}

// Getter: Cr 
double Monster::getCr(){
    return this->cr;
}

// Setter: CR 
void Monster::setCr(double cr){
    this->cr = cr;
}

// Getter: Type
string Monster::getType(){
    return this->type;
}

// Setter: Type 
void Monster::setType(string type){
    this->type = type;
}

// Getter: Size
string Monster::getSize(){
    return this->size;
}

// Setter: Size
void Monster::setSize(string size){
    this->size = size;
}

// Getter: Ac
int Monster::getAc() const {
    return this->ac;
}

// Setter: Ac
void Monster::setAc(int ac){
    this->ac = ac;
}

// Getter: Hp
int Monster::getHp() const {
    return this->hp;
}

// Setter: Hp
void Monster::setHp(int hp){
    this->hp = hp;
}

// Getter: Align
string Monster::getAlign(){
    return this->align;
}

// Setter: Align
void Monster::setAlign(string align){
    this->align = align;
}

// Overloading operator <
bool Monster::operator<(const Monster& other) const {
    return name < other.name;
}

// Overloading operator >
bool Monster::operator>(const Monster& other) const {
    return name > other.name;
}

// Overloading operator ==
bool Monster::operator==(const Monster& other) const {
    return name == other.name;
}

// Overloading operator !=
bool Monster::operator!=(const Monster& other) const {
    return name != other.name;
}

// print function
std::ostream& operator<<(std::ostream& os, const Monster& monster) {
    os << "Name: " << monster.name << endl;
    os << "cr: " << monster.cr << endl;
    os << "type: " << monster.type << endl;
    os << "size: " << monster.size << endl;
    os << "ac: " << monster.ac << endl;
    os << "hp: " << monster.hp << endl;
    os << "align: " << monster.align << endl;
    return os;
}