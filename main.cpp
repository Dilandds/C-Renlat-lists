#include <iostream>
#include "list"
#include <string>
#include <fstream>
#include "CustomerEntry.h"
#include "ListEntryInventory.h"
#include "Common.h"
#include "Inventory.h"
#include "Customers.h"

using namespace std;

//gloabal variables
int check =0;
int check_pending =0;
int check_rent = 0;

list <ListEntryInventory> Inventory::inventory;

//Functions to use in main
string getIndexLetter(string id){
    return id.substr(0,1);
}
int getIndex(string id){
    return stoi(id.substr(1,id.size()));
}
int main(int argc, char** argv) {
    //inventory_small.txt customer_small.txt output_inventory.txt output_customer.txt

    //arguments handing
    string in_i = argv[1];
    string in_c = argv[2];
    string out_i = argv[3];
    string out_c = argv[4];

    
    Inventory in;
    Customers cu;

    //reading inventory file
    ifstream infile(in_i);
    string id;
    int count;
    string name;
    while (infile >> id >> count >> name)
    {
        if(getIndex(id)<0 || getIndexLetter(id)!="T"){
            cerr << "Invalid inventory ID " << id <<" found in the inventory file." << endl;
        }else{
            ListEntryInventory li(id,count,name);
            in.addEntry(li);
        }

    }
    //reading customers file
    ifstream infile1(in_c);
    string id_customer;
    string purpose;
    float time;
    int count_customer;
    string item_id;
    string name_customer;
    while (infile1 >> id_customer >> purpose >> time >> count_customer >> item_id >> name_customer)
    {   
        //if the index is wrong
        if(getIndex(id_customer)<0 || getIndexLetter(id_customer)!="C"){
            cerr << "Invalid Customer ID " << id <<" found in the inventory file." << endl;
        }else{
            in.getItem(item_id);
            if(check==1){
                if(purpose=="rent"){
                    if(in.getItem(item_id)->getQuantity()>=count_customer){//have enough items to rent
                        //rent the requested quantity of items to the customer and adjust the inventory quantity
                        int remaining = in.getItem(item_id)->getQuantity()-count_customer;
                        in.getItem(item_id)->setQuantity(remaining);
                        CustomerEntry c(id_customer,name_customer,count_customer,time);
                        //adding to the rented list of a inventory
                        //When the inventory is empty
                        if(in.getItem(item_id)->rentSize()==0){
                            in.getItem(item_id)->rent.push_front(c);
                        //rent list of ainventory is not empty
                        }else{
                            in.getItem(item_id)->isRented(id_customer); //iterator of the customer
                            if(check_rent==1){ //if customer already exist update count
                                in.getItem(item_id)->isRented(id_customer)->setCount(in.getItem(item_id)->isRented(id_customer)->getCount()+count_customer);
                            }else{//customer is not included add it
                                in.getItem(item_id)->rent.push_front(c);
                            }
                        }
                        //add that item rented customer to the list
                        CustomerEntry *c1 = new CustomerEntry(id_customer,name_customer);
                        cu.addToList(c1);
                        //adding entry to customer ( adding the item to customer)
                        ListEntryInventory ent(item_id,count_customer);
                        cu.addToRent(ent,id_customer);
                    }else{//add that customer to pending ( no enough items )
                        CustomerEntry c(id_customer,name_customer,count_customer,time);
                        in.getItem(item_id)->addEntryPending(c);
                        //adding to customer list
                        CustomerEntry *c1 ;
                        c1 = new CustomerEntry(id_customer,name_customer);
                        cu.addToList(c1);
                        //adding entry to customer as pending
                        ListEntryInventory ent(item_id,count_customer);
                        cu.addToPending(ent,id_customer);

                    }
                }else if(purpose=="return"){
                    //first increase the avilable amount
                    in.getItem(item_id)->setQuantity(in.getItem(item_id)->getQuantity()+count_customer);
                    //then remove the returned person from rent list
                    in.getItem(item_id)->removeFromRent(id_customer);
                    // remove the returned as a rented coustomer
                    cu.removeFromRent(id_customer,item_id);
                //if return coutomer in waiting + inventory - pending
                in.getItem(item_id)->isPending(id_customer);
                if(check_pending==1){ //if the returning one is also waiting ( rare )
                    in.getItem(item_id)->setQuantity(in.getItem(item_id)->getQuantity()-count_customer);
                    in.getItem(item_id)->isPending(id_customer)->setCount( in.getItem(item_id)->isPending(id_customer)->getCount()-count_customer);
                }
                else{ //now check the pending list of returned item and give them if can
                    string test=in.getItem(item_id)->adjustPending(id_customer);
                   //if a customer changed from waiting to rent change it in coustomer list
                    if(test!="not_changed") {
                        string change_cus = test;
                        cu.changePending(change_cus, item_id);
                    }
                    }
                }

            }else{
                //id is wrong
                string t = (purpose=="return") ? " attempted to return item " : " requested ";
                cerr << "Customer" << id_customer << t << item_id << "which is not in the inventory";

            }
            check =0;
            check_rent = 0;
            check_pending = 0;

        }

    }



// remove empty customers from the list
   cu.removeEmpty();
   //write customers to the list
   cu.writeToFile(out_c);
//write inventory to a file
    in.writeToFile(out_i);


    return 0;



}
