#ifndef __ATM_H
#define __ATM_H
#include <list>
#include <iostream>
const int INITIALMONEY = 1000;
class Customer;

class ATM
{
public:
    ATM(int id);
    void insert_customer(Customer* customer);
    void display();
    //delete the first account int the queue, return the second service_time
    int dequeue(int time_slot);
    int customers();
private:
    int id;
    std::list<Customer*> queue;
    int money; //money in the atm, initial is 1,000
};
#endif
