#include "AccountFactory.h"
#include "PersonalAccount.h"
#include "BusinessAccount.h"

AccountFactory* AccountFactory::m_instance = NULL;

AccountFactory* AccountFactory::instance() {
    if (m_instance == NULL) {
        m_instance = new AccountFactory();
    }
    return m_instance;
}

Account* AccountFactory::getAccount(std::string type, std::string subtype) {
    if (type == "Personal") {
        if (subtype == "PSaving") {
            return new PSavingsAccount();
        }
        else if (subtype == "PChecking") {
            return new PCheckingAccount();
        }
        else if (subtype == "PMoneyMarket") {
            return new PMoneyMarketAccount();
        }
        else if (subtype == "PCertificates") {
            return new PCertificatesfDeposits();
        }
    }
    else if (type == "Business") {
        if (subtype == "BSaving") {
            return new BSavingAccount();
        }
        else if (subtype == "BChecking") {
            return new BSavingAccount();
        }
        else if (subtype == "BHighVolume") {
            return new BHighVolumeCheckingAccount();
        }
        else if (subtype == "BForeignCurrency") {
            return new BForeignCurrencyAccount();
        }
    }
    return NULL;
}