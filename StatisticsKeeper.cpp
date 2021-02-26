#include "StatisticsKeeper.h"
#include <cstddef>
#include <iostream>
#include "Customer.h"
#include "Account.h"

StatisticsKeeper* StatisticsKeeper::m_instance = NULL;
StatisticsKeeper::StatisticsKeeper() {
    this->sim_time = 0;
    this->atm_num = 0;
    this->sum_service_time = 0;
    this->sum_waiting_time = 0;
    this->transacton_count = 0;
    this->sum_money_deposited = 0;
    this->sum_money_withdrawn = 0;
    this->refill_count = 0;
}

StatisticsKeeper* StatisticsKeeper::instance() {
    if (m_instance == NULL) {
        m_instance = new StatisticsKeeper();
    }
    return m_instance;
}

void StatisticsKeeper::set_sim_time(int time) {
    this->sim_time = time;
}
void StatisticsKeeper::set_atm_num(int time) {
    this->atm_num = time;
}

void StatisticsKeeper::add_customer(Customer* customer) {
    customer_ids.insert(customer->get_id());
    this->sum_service_time += customer->get_service_time();
    std::string typedesc = customer->get_curr_account()->typedesc();
    if (account_typenum.find(typedesc) != account_typenum.end()) {
        ++account_typenum[typedesc];
    }
    else {
        account_typenum[typedesc] = 1;
    }
    Transaction* transaction = customer->get_transaction();
    TransType transtype = transaction->get_transtype();
    ++transacton_count;
    if (transacton_typenum.find(transtype) != transacton_typenum.end()) {
        ++transacton_typenum[transtype];
    }
    else {
        transacton_typenum[transtype] = 1;
    }
    if (transtype == WITHDRAWAL) {
        this->sum_money_withdrawn += transaction->get_transaction_money();
    }
    else if (transtype == DEPOSIT) {
        this->sum_money_deposited += transaction->get_transaction_money();
    }

    //std::cout << "====" << "exit:" << customer->get_exit_time() << " arr:" << customer->get_arrival_time() << " serv:" << customer->get_service_time() << std::endl;
    this->sum_waiting_time += (customer->get_exit_time() - customer->get_arrival_time() - customer->get_service_time());
    //std::cout << " sum wait time:" << this->sum_waiting_time << std::endl;

}

void StatisticsKeeper::add_atm_refill() {
    ++this->refill_count;
}

void StatisticsKeeper::report() {
    std::cout << "-------- report ---------------" << std::endl
        << "Duration of simulation: " << this->sim_time << std::endl
        << "Number of ATM machines: " << this->atm_num << std::endl
        << "Total no. of customers serviced: " <<this->customer_ids.size() << std::endl
        << "Total no. of customers serviced categorized by type of accounts: " << std::endl;
    for (std::map<std::string, int>::const_iterator iter = account_typenum.begin(); iter != account_typenum.end();
        ++iter) {
        std::cout << "    " << iter->first << ": " << iter->second << std::endl;
        }
    std::cout << "Average service time for each customer: " << (double)this->sum_service_time / customer_ids.size() << std::endl;
    std::cout << "Average waiting time for each customer: " << (double)this->sum_waiting_time / customer_ids.size() << std::endl;
    std::cout << "Total number of transactions: " << this->transacton_count << std::endl;
    for (std::map< TransType, int>::const_iterator iter = transacton_typenum.begin(); iter != transacton_typenum.end(); ++iter) {
        std::cout << Transaction::get_transaction_name(iter->first) << ": " << iter->second << std::endl;
    }
    std::cout << "Total amount of money deposited: " << this->sum_money_deposited << std::endl; 
    std::cout << "Total amount of money withdrawn: " << this->sum_money_withdrawn << std::endl;
    std::cout << "Number of refill_cash events generated: " << this->refill_count << std::endl;
     
    std::cout << "----------report end---------" << std::endl;/*
    int sim_time; //Duration of simulation
    int atm_num; //Number of ATM machines
    int customer_num; //Total no. of customers serviced
    //Total no. of customers serviced categorized by type of accounts
    //Average service time for each customer
    //Average waiting time for each customer
    //Total number of transactions
    //Total number of transactions categorized by type of transaction

    //Total amount of money deposited/withdrawn
    //Number of refill_cash events generated
    */
}
