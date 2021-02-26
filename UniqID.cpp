#include "UniqID.h"
UniqID* UniqID::m_instance = NULL;

UniqID::UniqID() {
    transactionID = 1;
    accountID = 1;
    customerID = 1;
    SSN = 1;
}

UniqID* UniqID::instance() {
    if (m_instance == NULL) {
        m_instance = new UniqID();
    }
    return m_instance;
}

int UniqID::genID(std::string idtype) {
    if (idtype == "transaction") {
        return transactionID++;
    }
    if (idtype == "account") {
        return accountID++;
    }
    if (idtype == "SSN") {
        return SSN++;
    }
    if (idtype == "customer") {
        return customerID++;
    }
    return -1;
}
