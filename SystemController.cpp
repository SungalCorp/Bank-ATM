#include "SystemController.h"
#include "TimingWheel.h"
#include "TrafficGenerator.h"
#include<iostream>

using namespace std;

SystemController* SystemController::m_instance = NULL;

SystemController* SystemController::instance() {
    if (m_instance == NULL) {
        m_instance = new SystemController();
    }
    return m_instance;
}
SystemController::~SystemController() {
    for (unsigned i = 0; i < atms.size(); ++i) {
        delete atms[i];
    }
    atms.clear();
}

void SystemController::init_atm(int atm_num) {
    for (int i = 0; i < atm_num; ++i) {
        atms.push_back(new ATM(i));
        atms_sum_service_time.push_back(0);
    }
}
void SystemController::choose_ATM(Customer* customer) {
    int min_index = -1;
    int min_time = -1;
    for (unsigned i = 0; i < atms.size(); ++i) {
        if (min_index == -1 || atms_sum_service_time[i] < min_time) {
            min_index = i;
            min_time = atms_sum_service_time[i];
        }
    }
    atms[min_index]->insert_customer(customer);
    atms_sum_service_time[min_index] += customer->get_service_time();
    //std::cout << "atm:" << min_index << " insert customer";
    //customer->display();
    //std::cout << std::endl;
    if (atms[min_index]->customers() == 1) {
        TimingWheel::instance()->insert(customer->get_service_time(), atms[min_index]);
        cout << "***" << customer->get_id() << " " << customer->get_service_time() << "is allocated ATM" << min_index << endl;
        //std::cout << "+++++insert ";
        //atms[min_index]->display();
        //std::cout << std::endl;
        //TimingWheel::instance()->display();
    }
}

void SystemController::show_atm_time() {

    //////////////
    std::cout << "=== ";
    for (unsigned i = 0; i < atms.size(); ++i) {
        std::cout << "atm" << i << " " << atms_sum_service_time[i] << " ";
    }
    std::cout << std::endl;
    //////////////////
}
void SystemController::simulate(std::list<Customer*> initial_customers, int atm_num, int sim_time) {
    init_atm(atm_num);

    for (std::list<Customer*>::const_iterator iter = initial_customers.begin(); iter != initial_customers.end(); ++iter) {
        choose_ATM(*iter);
    }
    //////////////
    //show_atm_time();
    //////////////////
    //TimingWheel::instance()->display();
    //std::cout << "+++++++after init+" << std::endl;


    std::list<Customer*> customers;

    for (int i = 0; i < sim_time; ++i) {
        //for(int i = 1; i < 30; ++i) {
        for (unsigned j = 0; j < atms.size(); ++j) {
            if (atms_sum_service_time[j] > 0) {
                --atms_sum_service_time[j];
            }
        }

        //std::cout << "t" << i << " try scheculd " << std::endl;
        TrafficGenerator::instance()->generate_dynamic_traffic(customers, i);
        //std::cout << "t" << i << " " << customers.size() << std::endl;
        for (std::list<Customer*>::const_iterator iter = customers.begin(); iter != customers.end(); ++iter) {
            choose_ATM(*iter);
            //show_atm_time();
        }
        TimingWheel::instance()->schedule();
        //std::cout << "---------" << std::endl;
    }
}
