#ifndef __Customer_H
#define __Customer_H
#include <vector>
#include <iostream>
#include "UniqID.h"
class Transaction;
class Account;
class Customer
{
public:
    Customer();
    ~Customer();
    //invoke transactions
    void set_service_time(int time);
    void set_arrival_time(int time);
    void set_exit_time(int time);
    void add_account(Account* account);
    int get_id();
    int get_service_time();
    int get_arrival_time();
    int get_exit_time();
    void display();
    void report_done();
    Account* get_curr_account();
    std::vector<Account*>& get_accounts();
    void set_transaction(Transaction* transaction);
    Transaction* get_transaction();
private:
    int id;
    //hold one or more accounts
    Transaction* transaction;
    std::vector<Account*> accounts;

    int arrival_time; //the customer joins the ATM queue
    int service_time; //how long he/she would use the ATM machine
    int exit_time; //when the customer in done
};
#endif
