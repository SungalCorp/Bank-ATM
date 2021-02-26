#ifndef __Transaction_H
#define __Transaction_H
#include "Account.h"

#include <string>

enum TransType { WITHDRAWAL, DEPOSIT, TRANSFER, BALANCE};

class Transaction
{
public:
    Transaction(TransType trans_type, Account* account);
    //void withdrawal();
    //void deposit();
    //void transafer();
    
    std::string balance(Account* account);//Balance Inquiry
    void set_transaction_money(int money);
    int get_transaction_money();
    TransType get_transtype();
    Account* get_initiator_account();
    static std::string get_transaction_name(TransType);

private:
    Account* initiator_account;
    Account* target_account;
    TransType trans_type;
    int transaction_money;
    int number; //transaction number
};
#endif
