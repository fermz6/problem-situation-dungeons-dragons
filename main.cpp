#include <iostream>
#include "catalog.h"
#include "dungeon.h"

using namespace std;

int main() {
    unsigned int    start = 0, end = 0;
    Catalog         myCatalog;
    Dungeon         myDungeon;

    if (!myCatalog.loadFromCSV("monsters.csv")) {
        cout << "Could not create the catalog" << endl;
        return 0;
    }

    cout << "Creating dungeon..." << endl;
    if (!myDungeon.loadMap("dungeon.txt")) {
        cout << "Could not load the dungeon map" << endl;
        return 0;
    }

    // one room for every vertex of the map: room i is vertex i
    for (unsigned int c = 0; c < myDungeon.getMapSize(); c++) {
        Monster *pMonster = myCatalog.getRandomMonster();
        if (!pMonster) {
            cout << "Could not get a monster from the catalog" << endl;
            return 0;
        }
        if (!myDungeon.createRoom(*pMonster)) {
            cout << "Could not add a room with a monster to the dungeon" << endl;
            return 0;
        }
    }
    myDungeon.printRooms();

    cout << "Choose a route:" << endl;
    do {
        cout << "Starting room: ";
        if (!(cin >> start))
            return 0;
        cout << "Final room: ";
        if (!(cin >> end))
            return 0;
    } while (start >= myDungeon.getMapSize() || end >= myDungeon.getMapSize() || start == end);

    if (!myDungeon.traceRoute(start, end)) {
        cout << "There is no route from " << start << " to " << end << endl;
        return 0;
    }
    myDungeon.printRoute();

    do {
        Room *current = myDungeon.currentRouteRoom();
        if (current)
            cout << "Entering " << *current << endl;
    } while (myDungeon.advanceRoute());

    return 0;
}
