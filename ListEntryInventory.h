
#ifndef RENTED_LISTENTRYINVENTORY_H
#define RENTED_LISTENTRYINVENTORY_H
#include "CustomerEntry.h"
#include <string>

class CustomerEntry;
class ListEntryInventory{
private:
    string id;
    int quantity;
    string name;

public:
    list <CustomerEntry> rent;
    list <CustomerEntry> pending;
    ListEntryInventory();
    ListEntryInventory(string _id,int _quantity,string _name);

    ListEntryInventory(string _id,int _count);
    string getId();
    int getQuantity();
    void  setQuantity(int q);
    string getName();
    list <CustomerEntry> getRent();
    list <CustomerEntry> getPending();
    int getIndex(string id);

    _List_iterator<CustomerEntry> isPending(string id);
    _List_iterator<CustomerEntry> isRented(string id);

    string adjustPending(string id);

    int pendingSize();
    int rentSize();
    void addEntryPending(CustomerEntry li);


    void removeFromRent(string cus_id);
};



#endif //RENTED_LISTENTRYINVENTORY_H
