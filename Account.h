#ifndef __Account_H
#define __Account_H
#include <string>
#include <sstream>
#include <iostream>

class Customer;
class Account {
public:
    Account();
    virtual ~Account() {}
    int getBalance();
    //virtual void deposit() = 0;
    //virtual void withdraw() = 0;
    virtual void report_done() = 0;
    std::string id();
    virtual std::string typedesc() = 0;
private:
    Customer* customer;
    std::string accountID;
    std::string SSN;
    std::string name;
    std::string address;
    int balance; // 15.34 -> 1534
};
#endif
