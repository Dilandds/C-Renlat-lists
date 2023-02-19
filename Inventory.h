
#include <iostream>
#ifndef RENTED_INVENTORY_H
#define RENTED_INVENTORY_H

using namespace std;
#include "ListEntryInventory.h"

class Inventory{
protected:
    static list <ListEntryInventory> inventory;
public:
    list <ListEntryInventory> getList();
    int getIndex(string id);
    void addEntry(ListEntryInventory li);

    _List_iterator<ListEntryInventory> getItem(string id);

    void printList();
    void print();
    void writeToFile(string filename);


};

#endif //RENTED_INVENTORY_H
