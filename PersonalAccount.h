#ifndef __PersonalAccount_H
#define __PersonalAccount_H

#include "Account.h"
#include <string>
class PersonalAccount :
    public Account
{
public:
    void report_done() {
        std::cout << id() << " PersonalAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "Personal";
    }
};

class PSavingsAccount : public PersonalAccount {
public:
    void report_done() {
        std::cout << id() << " PSavingsAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "PSavingsAccount";
    }
};

class PCheckingAccount : public PersonalAccount {
public:
    void report_done() {
        std::cout << id() << " PCheckingAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "PCheckingAccount";
    }
};
class PMoneyMarketAccount : public PersonalAccount {
public:
    void report_done() {
        std::cout << id() << " PMoneyMarketAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "PMoneyMarketAccount";
    }
};
class PCertificatesfDeposits : public PersonalAccount {
public:
    void report_done() {
        std::cout << id() << " PCertificatesfDeposits is done" << std::endl;
    }

    std::string typedesc() {
        return "PCertificatesfDeposits";
    }
};
#endif
