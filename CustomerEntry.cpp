
#include "CustomerEntry.h"


CustomerEntry::CustomerEntry(){

}
CustomerEntry::CustomerEntry(string _id, string _name,int _count,float _time){
    name = _name;
    id = _id;
    count = _count;
    time = _time;
}
CustomerEntry::CustomerEntry(string _id, string _name){
    name = _name;
    id = _id;
}
string CustomerEntry::getName(){
    return name;
}

float CustomerEntry::getTime(){
    return time;
}

string CustomerEntry::getId(){
    return id;
}
int CustomerEntry::getCount(){
    return count;
}
void CustomerEntry::setCount(int c){
    count = c;
}

list <ListEntryInventory> CustomerEntry::getPendingList(){
    return pending;
}
list <ListEntryInventory> CustomerEntry::getRentList(){
    return rent;
}

void CustomerEntry::addToRent(ListEntryInventory li){
    list<ListEntryInventory>::iterator it;
    for (it = rent.begin(); it != rent.end(); ++it){
        if(li.getId()==it->getId()){
            it->setQuantity(it->getQuantity()+li.getQuantity());
            return;
        }
    }
    rent.push_back(li);
}
void CustomerEntry::addToPending(ListEntryInventory li){
    list<ListEntryInventory>::iterator it;
    for (it = pending.begin(); it != pending.end(); ++it){
        if(li.getId()==it->getId()){
            it->setQuantity(it->getQuantity()+li.getQuantity());
            return;
        }
    }
    pending.push_back(li);
}




