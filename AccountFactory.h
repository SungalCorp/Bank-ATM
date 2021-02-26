#ifndef __AccountFactory_H
#define __AccountFactory_H
#include "Account.h"
#include <string>
class AccountFactory
{
public:
    static AccountFactory* instance();
    Account* getAccount(std::string type, std::string subtype);
private:
    static AccountFactory* m_instance;
    AccountFactory() {}
};
#endif
