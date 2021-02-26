#ifndef __UniqID_H
#define __UniqID_H

#include <string>
class UniqID
{
public:
    static UniqID* instance();
    int genID(std::string idtype);
private:
    int transactionID;
    int accountID;
    int customerID;
    int SSN;
    static UniqID* m_instance;
    UniqID();
};
#endif
