
#ifndef RENTED_CUSTOMERS_H
#define RENTED_CUSTOMERS_H
#include <iostream>

#include "CustomerEntry.h"

class Customers{
private:
public:
    list <CustomerEntry> customer_list;
    int getIndex(string id);
    void addToList(CustomerEntry *li);
    void changePending(string cus_id,string item_id);
    void print();
    void addToRent(ListEntryInventory li,string cus_id);
    void addToPending(ListEntryInventory li,string cus_id);

    void removeFromRent(string cus_id,string item_id);
    void removeEmpty();
    void writeToFile(string file);
};



#endif //RENTED_CUSTOMERS_H
