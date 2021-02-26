#ifndef __SystemController_H
#define __SystemController_H
#include <list>
#include <vector>
#include "Customer.h"
#include "ATM.h"

class SystemController
{
public:
    static SystemController* instance();
    void simulate(std::list<Customer*> initial_customers, int atm_num, int sim_time);
private:
    void init_atm(int atm_num);
    void choose_ATM(Customer* customer);
    void show_atm_time();
    std::vector<ATM*> atms;
    std::vector<int> atms_sum_service_time;
    static SystemController* m_instance;
    SystemController() {}
    ~SystemController();
};
#endif
