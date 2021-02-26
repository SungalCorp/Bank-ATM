#include "Account.h"
#include "UniqID.h"

Account::Account() {
    std::stringstream ss;
    ss << UniqID::instance()->genID("account");
    accountID = ss.str();
}

std::string Account::id() {
    return accountID;
}
int Account::getBalance() {
    return balance;
}
