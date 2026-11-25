/*
Description: Main, implementation and correlation of all the codes
Author: Fernanda Magaña Zapata
ID: A01663341
Date: November 2026
*/

#include "Catalog.h"
#include "Room.h"
#include "Dungeon.h"
#include "Player.h"
#include "HashTable.h"
#include "AVLTree.h"

#define NUM_ROOMS 20

using namespace std;

// Used by the function pointer of Hash Table
unsigned int internalHash(const string &data){
    unsigned int hash = 0;
    unsigned int size = data.size();

    for(unsigned int i = 0; i < size; i++)
        hash = hash * 31 + data[i];
    
    return hash;
}

// Function that always returns 0
unsigned int hashZero(const int & ){
    return 0;
}

int main() {
    srand(time(nullptr));
    Catalog myCatalog;
    Dungeon myDungeon;
    string name;
    string race;

    cout << "Loading creature file..." << endl;

    if(!myCatalog.load("monsters.csv")){
        cout << "Could not create the catalog" << endl;
        return 1;
    }

    cout << "Catalog: " << myCatalog.getCount() << " monsters laoded !" << endl;
    cout << "HashTable: ";
    myCatalog.printStats();

    cout << endl;
    cout << "Find \"Goblin\": " << endl;
    Monster *target = myCatalog.findByName("goblin");
    if(!target){
        cout << "No target in catalog" << endl;
    } else {
        cout << *target << endl;
    }

    cout << "Find \"Unicorn Cat\": " << endl;
    target = myCatalog.findByName("unicorn cat");
    if(!target){
        cout << "No target in catalog" << endl;
    } else {
        cout << *target << endl;
    }

    HashTable<int> worstCase;
    if(!worstCase.createTable(11, hashZero))
        return 1;
    
    for(unsigned int i = 0; i < 1000; i++){
        if(!worstCase.insert(i)){
            cout << "Could not insert elements" << endl;
            return 1;
        }
    }

    cout << endl;
    cout << "Worst case (hash always 0): ";
    worstCase.printStats();

    cout << endl;
    cout << "Find 500: ";
    if(!worstCase.find(500)){
        cout << "Not found" << endl;
    }
    else{
        cout << "Found" << endl;
    }

    cout << endl;
    cout << "Find 1000: ";
    if(!worstCase.find(1000)){
        cout << "Not found" << endl;
    }
    else{
        cout << "Found" << endl;
    }

    AVLTree<int> avlCase;
    for(unsigned int i = 0; i < 1000; i++){
        if(!avlCase.insert(i)){
            cout << "AVL node could not be inserted" << endl;
            return 1;
        }
    }

    cout << endl;
    cout << "AVL Tree with 0... 999: height " << avlCase.height();
    cout << ", first 10: ";
    auto it = avlCase.begin();
    for(unsigned int i = 0; i < 10 && it != avlCase.end(); i++){
        cout << *it << " ";
        ++it;
    }

    cout << endl;
    cout << "Creating dungeon..." << endl;
    for(int c = 0; c < NUM_ROOMS; c++) {
        Monster *pMonster = nullptr;

        pMonster = myCatalog.getRandom();
        if(!pMonster){
            cout << "Could not get a monster from the catalog" << endl;
            return 1;
        }

        if(!myDungeon.createRoom(*pMonster)) {
            cout << "Could not add a room with a monster to the dungeon." << endl;
            return 1;
        }
    }

    myDungeon.print();
    
    cout << endl;
    cout << "Enter player name: ";
    cin >> name;

    cout << "Enter player race (elf, human, dwarf): ";
    cin >> race;

    while(race != "elf" && race != "human" && race != "dwarf"){
        cout << "Invalid race. Enter race again: ";
        cin >> race;
    }

    Player myPlayer(name, race);
    cout << "Player: " << myPlayer << endl;

    return 0;
}