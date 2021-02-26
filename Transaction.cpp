#include "Transaction.h"
#include "UniqID.h"
#include <sstream>

Transaction::Transaction(TransType trans_type, Account* initiator_account) {
    number = UniqID::instance()->genID("transaction");
    this->initiator_account = initiator_account;
    this->trans_type = trans_type;
    target_account = NULL;
}

std::string Transaction::balance(Account* account) {
    int balance = account->getBalance();
    std::stringstream ss;
    ss << balance / 100 << "." << balance % 100;
    return ss.str();
}

Account* Transaction::get_initiator_account() {
    return initiator_account;
}

TransType Transaction::get_transtype() {
    return this->trans_type;
}

//WITHDRAWAL, DEPOSIT, TRANSFER, BALANCE
std::string Transaction::get_transaction_name(TransType transtype) {
    switch (transtype) {
    case WITHDRAWAL:
        return "WITHDRAWAL";
    case DEPOSIT:
        return "DEPOSIT";
    case TRANSFER:
        return "TRANSFER";
    case BALANCE:
        return "BALANCE";
    }
    return "";
}

void Transaction::set_transaction_money(int money) {
    this->transaction_money = money;
}
int Transaction::get_transaction_money() {
    return this->transaction_money;
}
