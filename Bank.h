#ifndef __BANK_H
#define __BANK_H
#include <list>
#include <string>
class Customer;

class Bank
{
public:
    Bank();
    void set_inputfile(std::string filename);
    void set_atm_num(int);
    void set_sim_time(int time);
    void generate_customerbase();
    void generate_initial_traffic();
    void simulate();
    void report();
private:
    int atm_num;
    std::list<Customer*> initial_customers;
    int sim_time;
    std::string filename;
};
#endif
