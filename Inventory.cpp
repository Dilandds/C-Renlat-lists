#include <fstream>
#include "Inventory.h"
#include "Common.h"
#include <iostream>


list <ListEntryInventory> Inventory::getList(){
    return inventory;
}
int Inventory::getIndex(string id){
    return stoi(id.substr(1,id.size()));
}
void Inventory::addEntry(ListEntryInventory li){
    int index = getIndex(li.getId());
    list<ListEntryInventory>::iterator it;
    int check1 =0;
    int check2 = 0;

    if(inventory.size()==0){

        it = inventory.begin();

        inventory.insert(it, li);
        check2 = 1;

    }else {
        for (it = inventory.begin(); it != inventory.end(); ++it) {
            int Ind = getIndex(it->getId());
            cout << Ind << endl;
            if (Ind > index) {
                inventory.insert(it, li);
                check1 = 1;
                break;

            } else {
                continue;
            }
        }
    }
    if(check2==0 && check1 == 0){
        it = inventory.end();
        inventory.insert(it, li);
    }




}

_List_iterator<ListEntryInventory> Inventory::getItem(string id){
    int index = getIndex(id);
    ListEntryInventory e("empty",0,"empty");
    list<ListEntryInventory>::iterator it;
    for (it = inventory.begin(); it != inventory.end(); ++it) {
        if(getIndex(it->getId())==index){
            check =1;
            return it;
        }
    }
    return it;


}

void Inventory::printList(){
    list<ListEntryInventory>::iterator it;
    cout << inventory.size() << endl;

    for (it=inventory.begin(); it!=inventory.end(); ++it)
        std::cout << ' ' << it->getId() << " " <<it->getQuantity()<< " " << it->rentSize()  <<  it->pendingSize() <<endl;
    std::cout << '\n';
}
void Inventory::print(){
    list<ListEntryInventory>::iterator it;
    for (it=inventory.begin(); it!=inventory.end(); ++it){
        cout << ' ' << it->getId() << " " <<it->getQuantity()<< " " ;
        list<CustomerEntry>::iterator it1;
        if(it->pending.size()!=0){
            for (it1=it->pending.begin(); it1!=it->pending.end(); ++it1){
                cout << it1->getName() << " " << it1->getCount() << endl;
            }

        }




    }
}
void Inventory::writeToFile(string filename){
    ofstream MyFile(filename);
    list<ListEntryInventory>::iterator it;
    for (it=inventory.begin(); it!=inventory.end(); ++it){
        MyFile << it->getId() << " " <<it->getQuantity()<< " available " << it->getName() << endl ;
        list<CustomerEntry>::iterator it1;
        if(it->rent.size()>0){
            MyFile << "Rental Customers:";
            for (it1=it->rent.begin(); it1!=it->rent.end(); ++it1) {
                MyFile << " " << it1->getId() << " "<< it1->getName() << " " << "(" << it1->getCount() << ")" ;
            }
            MyFile << endl;
        }
        if(it->pending.size()>0){
            MyFile << "Pending Customers:";
            for (it1=it->pending.begin(); it1!=it->pending.end(); ++it1) {
                MyFile << " " << it1->getId() << " "<< it1->getName() << " " << "(" << it1->getCount() << ")" ;
            }
            MyFile << endl;
        }
        MyFile << endl;
    }

    MyFile.close();
}




