#ifndef __StatisticsKeeper_H
#define __StatisticsKeeper_H

#include <map>
#include <string>
#include <set>
#include "Transaction.h"

class Customer;
class Transaction;

class StatisticsKeeper
{
public:
    static StatisticsKeeper* instance();
    void set_sim_time(int time);
    void set_atm_num(int time);
    void add_customer(Customer* customer);
    void add_atm_refill();
    //do the final report
    void report();

private:
    static StatisticsKeeper* m_instance;
    StatisticsKeeper();

    int sim_time; //Duration of simulation
    int atm_num; //Number of ATM machines
    std::set<int> customer_ids; // Total no.of customers serviced
   
    //Total no. of customers serviced categorized by type of accounts
    std::map < std::string, int> account_typenum;
    int transacton_count;
    std::map< TransType, int> transacton_typenum;
    int sum_service_time; //Average service time for each customer
    int sum_waiting_time;//Average waiting time for each customer

    int sum_money_deposited;
    int sum_money_withdrawn;
    int refill_count;
    //Total number of transactions
    //Total number of transactions categorized by type of transaction
    //Total amount of money deposited/withdrawn
    //Number of refill_cash events generated
};
#endif
