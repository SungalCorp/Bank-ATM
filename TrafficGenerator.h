#ifndef __TrafficGenerator_H
#define __TrafficGenerator_H

#include <vector>
#include <list>
#include <string>
#include "Customer.h"

/**
 * generates
 *   the customer base
 *   --the total number of customers that hold accounts in the bank
 *
 *   initial traffic
 *   --the number of customers in line to use the ATM when simulation starts
 *   dynamic player traffic
 *   --customers that will arrive during the simulation.
 * */

class TrafficGenerator
{
public:
    static TrafficGenerator* instance();
    void generate_customerbase(std::string filename);
    void generate_initial_traffic(std::list<Customer*>& customers);
    void generate_dynamic_traffic(std::list<Customer*>& customers, int arrival_time);
    void reuse(Customer* customer);
    ~TrafficGenerator();
private:
    static TrafficGenerator* m_instance;
    TrafficGenerator();
    void parse(std::string filename);
    Customer* choose_customer(int arrival_time);

    std::vector<Customer*> customer_base;
    std::list<Customer*> customer_unused;

    int base_count; //200
    int initial_count; //5
    int time_coming; // 0-2
    int service_time[2]; //5-12
    int multi_accounts_ratio; //80
    int pb_ratio[2]; //65, 35
    int saving_ratio[2]; // 50 30
    int checking_ratio[2]; // 35 55
    int money_market_ratio[2]; //8 0
    int certificater_ratio[2]; //12 0
    int high_volume_ratio[2]; // 0 10
    int foreign_ratio[2]; //0 5
};
#endif
