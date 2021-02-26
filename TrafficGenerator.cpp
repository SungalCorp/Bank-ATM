#include "TrafficGenerator.h"
#include <iostream>
#include <fstream>
#include "AccountFactory.h"
#include "Transaction.h"
#include <stdlib.h>

TrafficGenerator* TrafficGenerator::m_instance = NULL;
TrafficGenerator* TrafficGenerator::instance() {
    if (m_instance == NULL) {
        m_instance = new TrafficGenerator();
    }
    return m_instance;
}

TrafficGenerator::TrafficGenerator() {
    base_count = 0;
    initial_count = 0;
    time_coming = 0;
    multi_accounts_ratio = 0;
    for (int i = 0; i < 2; ++i) {
        service_time[i] = 0;
        pb_ratio[i] = 0;
        saving_ratio[i] = 0;
        checking_ratio[i] = 0;
        money_market_ratio[i] = 0;
        certificater_ratio[i] = 0;
        high_volume_ratio[i] = 0;
        foreign_ratio[i] = 0;
    }

    /*
    for(int i = 0; i < customer_base.size(); ++i) {
        delete customer_base
    }*/
}
void TrafficGenerator::parse(std::string filename) {
    std::ifstream infile(filename.c_str(), std::ifstream::in);
    if (!infile.is_open()) {
        std::cout << "cannot open " << filename << std::endl;
        exit(1);
    }
    infile >> base_count >> initial_count >> time_coming;
    infile >> service_time[0] >> service_time[1];
    infile >> multi_accounts_ratio;
    std::string flag;
    while (infile >> flag) {
        if (flag == "Personal") {
            infile >> pb_ratio[0];
        }
        else if (flag == "Business") {
            infile >> pb_ratio[1];
        }
        else if (flag == "Savings") {
            infile >> saving_ratio[0] >> saving_ratio[1];
        }
        else if (flag == "Checking") {
            infile >> checking_ratio[0] >> checking_ratio[1];
        }
        else if (flag == "Money") {
            infile >> flag >> money_market_ratio[0] >> money_market_ratio[1];
        }
        else if (flag == "Certificate") {
            infile >> flag >> flag >> certificater_ratio[0] >> certificater_ratio[1];
        }
        else if (flag == "High") {
            infile >> flag >> flag >> high_volume_ratio[0] >> high_volume_ratio[1];
        }
        else if (flag == "Foreign") {
            infile >> flag >> foreign_ratio[0] >> foreign_ratio[1];
        }
    }
    infile.close();
    //std::cout << "person:" << pb_ratio[0] << ", busi:" << pb_ratio[1] << std::endl;
    //std::cout << "money:" << money_market_ratio[0] << " " << money_market_ratio[1] << std::endl;
    //std::cout << "foreign:" << foreign_ratio[0] << " " << foreign_ratio[1] << std::endl;
}

//200 customer
// every customer
// --service time random [5,12]
// --random[0,100), [0,20) one acount, [20,..) multi account
//
// every account
// --rand1:[0,100),  Personal or Business
// --rand2:[0,100), subtype
void TrafficGenerator::generate_customerbase(std::string filename) {
    parse(filename);

    //std::cout << "generate_customerbase," << base_count << "," << initial_count << std::endl;
    for (int i = 0; i < base_count; ++i) {
        Customer* customer = new Customer();
        customer->set_service_time(rand() % (service_time[1] - service_time[0] + 1) + service_time[0]);
        //std::cout << " rand service_time:" << customer->get_service_time() << std::endl;
        int account_num = rand() % 100 > multi_accounts_ratio ? 1 : 2;
        Account* account = NULL;
        for (int j = 0; j < account_num; ++j) {
            bool person_flag = rand() % 100 < pb_ratio[0];
            int subrand = rand() % 100;
            std::string subtype;
            if (person_flag) {
                if (subrand < saving_ratio[0]) {
                    subtype = "PSaving";
                }
                else if (subrand < saving_ratio[0] + checking_ratio[0]) {
                    subtype = "PChecking";
                }
                else if (subrand < saving_ratio[0] + checking_ratio[0] + money_market_ratio[0]) {
                    subtype = "PMoneyMarket";
                }
                else {
                    subtype = "PCertificates";
                }
                account = AccountFactory::instance()->getAccount("Personal", subtype);
            }
            else {
                if (subrand < saving_ratio[1]) {
                    subtype = "BSaving";
                }
                else if (subrand < saving_ratio[1] + checking_ratio[1]) {
                    subtype = "BChecking";
                }
                else if (subrand < saving_ratio[1] + checking_ratio[1] + high_volume_ratio[1]) {
                    subtype = "BHighVolume";
                }
                else {
                    subtype = "BForeignCurrency";
                }
                account = AccountFactory::instance()->getAccount("Business", subtype);
            }

            if (account != NULL) {
                customer->add_account(account);
            }
        }
        customer_base.push_back(customer);
    }

    for (std::vector<Customer*>::const_iterator iter = customer_base.begin(); iter != customer_base.end(); ++iter) {
        customer_unused.push_back(*iter);
    }
}

Customer* TrafficGenerator::choose_customer(int arrival_time) {
    int index = rand() % customer_unused.size();
    std::list<Customer*>::iterator iter = customer_unused.begin();
    for (int i = 0; i < index; ++i) {
        ++iter;
    }
    Customer* customer = *iter;
    customer->set_arrival_time(arrival_time);
    std::vector<Account*> accounts = customer->get_accounts();
    if (accounts.size() == 0) {
        std::cout << "account zero!!!!!!!!!!" << std::endl;
    }
   
    int rand_account1 = rand() % accounts.size();
    customer_unused.erase(iter);
    Account* curr_account = accounts[rand_account1];
    
    Transaction* transaction = NULL; // new Transaction();
    //money between 100-2000
    switch(rand() % 4) {
        case 0:
            transaction = new Transaction(WITHDRAWAL, curr_account);
            transaction->set_transaction_money((rand() % 19 + 1) * 100);
            break;
        case 1:
            transaction = new Transaction(DEPOSIT, curr_account);
            transaction->set_transaction_money((rand() % 19 + 1) * 100);
            break;
        case 2:
            transaction = new Transaction(TRANSFER, curr_account);
            transaction->set_transaction_money((rand() % 19 + 1) * 100);
            break;
        case 3:
            transaction = new Transaction(BALANCE, curr_account);
            break;
        default:
            break;
    }

    customer->set_transaction(transaction);
    return customer;
}

void TrafficGenerator::generate_initial_traffic(std::list<Customer*>& customers) {
    customers.clear();
    for (int i = 0; i < initial_count; ++i) {
        customers.push_back(choose_customer(0));
    }
}

void TrafficGenerator::generate_dynamic_traffic(std::list<Customer*>& customers, int arrival_time) {
    customers.clear();

    int r = rand() % (time_coming + 1);
    for (int i = 0; i < r; ++i) {
        if (customer_unused.size() == 0) {
            break;
        }
        customers.push_back(choose_customer(arrival_time));
    }
}

void TrafficGenerator::reuse(Customer* customer) {
    customer_unused.push_back(customer);
}

TrafficGenerator::~TrafficGenerator() {
    for (unsigned i = 0; i < customer_base.size(); ++i) {
        delete customer_base[i];
    }
    customer_base.clear();
    customer_unused.clear();
}
