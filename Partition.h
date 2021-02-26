#ifndef __Partition_H
#define __Partition_H
class ATM;
class Partition
{
public:
    Partition();
    Partition(ATM* atmp, Partition* next);
    Partition* next();
    ATM* get_ATM();

private:
    ATM* atmp;
    Partition* nextp;
};
#endif
