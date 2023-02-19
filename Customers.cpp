#include <iostream>
#include "Customers.h"
#include <fstream>


int Customers::getIndex(string id){
    return stoi(id.substr(1,id.size()));
}
void Customers::addToList(CustomerEntry *li){
    int index = getIndex(li->getId());
    list<CustomerEntry>::iterator it;
    int check1 =0;
    int check2 = 0;

    if(customer_list.size()==0){

        it = customer_list.begin();

        customer_list.insert(it, *li);
        check2 = 1;

    }else {
        for (it = customer_list.begin(); it != customer_list.end(); ++it) {
            int Ind = getIndex(it->getId());
            if (Ind > index) {
                customer_list.insert(it, *li);
                check1 = 1;
                break;

            }else if(Ind == index){
                check1= 1;
                break;
            }
            else {
                continue;
            }
        }
    }
    if(check2==0 && check1 == 0){
        it = customer_list.end();
        customer_list.insert(it, *li);
    }
}
void Customers::changePending(string cus_id,string item_id){
    list<CustomerEntry>::iterator it;
    for (it = customer_list.begin(); it != customer_list.end(); ++it) {
        if(cus_id==it->getId()){
            list<ListEntryInventory>::iterator it1;
            for (it1 = it->pending.begin(); it1 != it->pending.end(); ++it1) {
                if(item_id==it1->getId()){
                    it->rent.push_back(*it1);
                    it->pending.erase(it1);
                    break;
                }

            }

        }

    }

}

void Customers::print(){
    list<CustomerEntry>::iterator it;
    for (it = customer_list.begin(); it != customer_list.end(); ++it) {
        cout << it->getId() << " " << it->getName() << " " << it->rent.size() << it->pending.size()<< endl ;
    }

}
void Customers::addToRent(ListEntryInventory li,string cus_id){
    list<CustomerEntry>::iterator it;
    for (it = customer_list.begin(); it != customer_list.end(); ++it) {
        if(cus_id==it->getId()){
            list<ListEntryInventory>::iterator it1;
            for (it1=it->rent.begin(); it1!=it->rent.end(); ++it1){
                if(li.getId()==it1->getId()){
                    it1->setQuantity(it1->getQuantity()+li.getQuantity());
                    return;
                }

            }
            it->rent.push_back(li);
        }
    }
}
void Customers::addToPending(ListEntryInventory li,string cus_id){
    list<CustomerEntry>::iterator it;
    for (it = customer_list.begin(); it != customer_list.end(); ++it) {
        if(cus_id==it->getId()){
            list<ListEntryInventory>::iterator it1;
            for (it1=it->pending.begin(); it1!=it->pending.end(); ++it1){
                if(li.getId()==it1->getId()){
                    it1->setQuantity(it1->getQuantity()+li.getQuantity());
                    return;
                }

            }
            it->pending.push_back(li);
        }
    }
}

void Customers::removeFromRent(string cus_id,string item_id){
    list<CustomerEntry>::iterator it;
    for (it = customer_list.begin(); it != customer_list.end(); ++it) {
        if(cus_id==it->getId()){
            list<ListEntryInventory>::iterator it1;
            for (it1=it->rent.begin(); it1!=it->rent.end(); ++it1){
                if(item_id==it1->getId()){
                    it->rent.erase(it1);
                    return;
                }
            }

        }
    }
}
void Customers::removeEmpty(){
    list<CustomerEntry>::iterator it;
    for (it = customer_list.begin(); it != customer_list.end(); ++it) {
        if(it->rent.size()==0 && it->pending.size()==0){
            customer_list.erase(it);
            return;
        }
    }


}
void Customers::writeToFile(string file){
    ofstream MyFile(file);
    list<CustomerEntry>::iterator it;
    for (it=customer_list.begin(); it!=customer_list.end(); ++it){
        if(it->rent.size()>0 || it->pending.size()>0 ) {
            MyFile << it->getId() << " " << it->getName() << endl;
            list<ListEntryInventory>::iterator it1;
            if (it->rent.size() > 0) {
                MyFile << "Rental:";
                for (it1 = it->rent.begin(); it1 != it->rent.end(); ++it1) {
                    MyFile << " " << it1->getId() << " " << "(" << it1->getQuantity() << ")";
                }
                MyFile << endl;
            }
            if (it->pending.size() > 0) {
                MyFile << "Pending:";
                for (it1 = it->pending.begin(); it1 != it->pending.end(); ++it1) {
                    MyFile << " " << it1->getId() << " " << "(" << it1->getQuantity() << ")";
                }
                MyFile << endl;
            }
            MyFile << endl;
        }
    }

    MyFile.close();

}
