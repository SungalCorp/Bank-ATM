#ifndef __BusinessAccount_H
#define __BusinessAccount_H

#include "Account.h"
class BusinessAccount :
    public Account
{
public:
    void report_done() {
        std::cout << id() << " BusinessAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "Business";
    }
};

class BSavingAccount : public BusinessAccount {
public:
    void report_done() {
        std::cout << id() << " BSavingAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "BSavingAccount";
    }
};
class BCheckingAccount : public BusinessAccount {
public:
    void report_done() {
        std::cout << id() << " BCheckingAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "BCheckingAccount";
    }
};
class BHighVolumeCheckingAccount : public BusinessAccount {
public:
    void report_done() {
        std::cout << id() << " BHighVolumeCheckingAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "BHighVolumeCheckingAccount";
    }
};
class BForeignCurrencyAccount : public BusinessAccount {
public:
    void report_done() {
        std::cout << id() << " BForeignCurrencyAccount is done" << std::endl;
    }
    std::string typedesc() {
        return "BForeignCurrencyAccount";
    }
};
#endif
