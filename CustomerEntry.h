
#ifndef RENT_LIST_1_CUSTOMERENTRY_H
#define RENT_LIST_1_CUSTOMERENTRY_H
using namespace std;
#include "list"
#include "ListEntryInventory.h"
#include <string>

class ListEntryInventory;
class CustomerEntry{
private:
    string name;
    string id;
    int count;
    float time;

public:
    list <ListEntryInventory> pending;
    list <ListEntryInventory> rent;
    CustomerEntry();
    CustomerEntry(string _id, string _name,int _count,float _time);
    CustomerEntry(string _id, string _name);

    float getTime();
    string getId();
    int getCount();
    void setCount(int c);
    list <ListEntryInventory> getPendingList();
    list <ListEntryInventory> getRentList();
    void addToRent(ListEntryInventory li);
    void addToPending(ListEntryInventory li);


    string getName();
};



#endif //RENT_LIST_1_CUSTOMERENTRY_H
