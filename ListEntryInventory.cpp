#include <iostream>
#include "ListEntryInventory.h"
#include "Common.h"

ListEntryInventory::ListEntryInventory(){

}
ListEntryInventory::ListEntryInventory(string _id,int _quantity,string _name){
    id = _id;
    quantity = _quantity;
    name = _name;
}

ListEntryInventory::ListEntryInventory(string _id,int _count){
    id = _id;
    quantity = _count;
}
string ListEntryInventory::getId(){
    return id;
}
int ListEntryInventory::getQuantity() {
    return quantity;
}
void  ListEntryInventory::setQuantity(int q){
    quantity=q;
}
string ListEntryInventory::getName(){
    return name;
}
list <CustomerEntry> ListEntryInventory::getRent(){
    return rent;
}
list <CustomerEntry> ListEntryInventory::getPending(){
    return pending;
}
int ListEntryInventory::getIndex(string id){
    return stoi(id.substr(1,id.size()));
}

_List_iterator<CustomerEntry> ListEntryInventory::isPending(string id){
    int index = getIndex(id);
    list<CustomerEntry>::iterator it;
    for (it = pending.begin(); it != pending.end(); ++it){
        if(getIndex(it->getId())==index){
            check_pending = 1;
            return it;
        }
    }
    return it;
}
_List_iterator<CustomerEntry> ListEntryInventory::isRented(string id){

    int index = getIndex(id);
    list<CustomerEntry>::iterator it;
    for (it = rent.begin(); it != rent.end(); ++it){
        if(getIndex(it->getId())==index){
            check_rent =1;
            return it;
        }
    }
    return it;
}

string ListEntryInventory::adjustPending(string id){
    list<CustomerEntry>::iterator it;
    for (it = this->pending.begin(); it != this->pending.end(); ++it) {
        if(it->getCount()<=this->getQuantity() ){
            //reduce quantity
            this->setQuantity(this->getQuantity()-it->getCount());
            //add to rent
            this->rent.push_back(*it);
            this->pending.erase(it);
            return it->getId();
        }
    }
    return "not_changed";
}

void ListEntryInventory::removeFromRent(string cus_id){
    list<CustomerEntry>::iterator it;
    for (it = this->rent.begin(); it != this->pending.end(); ++it) {
        if(cus_id== it->getId()){
            this->rent.erase(it);
            return;
        }
    }
    return;
}

int ListEntryInventory::pendingSize(){
    return pending.size();
}
int ListEntryInventory::rentSize(){
    return rent.size();
}
void ListEntryInventory::addEntryPending(CustomerEntry li){
    int index = li.getTime();
    list<CustomerEntry>::iterator it;
    int check1 =0;
    int check2 = 0;

    if(pending.size()==0){
        it = pending.begin();
        pending.insert(it, li);
        check2 = 1;

    }else {
        for (it = pending.begin(); it != pending.end(); ++it) {
            int Ind = getIndex(it->getId());
            if (Ind >= index) {
                pending.insert(it, li);
                check1 = 1;
                break;

            } else {
                continue;
            }
        }
    }
    if(check2==0 && check1 == 0){
        it = pending.end();
        pending.insert(it, li);
    }
}



