#include "Bank.h"
#include "TrafficGenerator.h"
#include "SystemController.h"
#include "StatisticsKeeper.h"
#include <stdlib.h>

Bank::Bank() {
    srand(0);
}
void Bank::set_inputfile(std::string filename) {
    this->filename = filename;
}

void Bank::set_atm_num(int ATMs) {
    this->atm_num = ATMs;
    StatisticsKeeper::instance()->set_atm_num(ATMs);
}


void Bank::set_sim_time(int time) {
    this->sim_time = time;
    StatisticsKeeper::instance()->set_sim_time(time);
}

void Bank::generate_customerbase() {
    TrafficGenerator::instance()->generate_customerbase(filename);
}

void Bank::generate_initial_traffic() {
    TrafficGenerator::instance()->generate_initial_traffic(initial_customers);
}

void Bank::simulate() {
    //insert one partition for each ATM in the timing wheel in curr_time_slot
    /*for(int i = 0; i < ATMs; ++i) {
        TimingWheel::instance()->insert(0, atms[i]);
    }*/

    SystemController::instance()->simulate(initial_customers, atm_num, sim_time);
}
void Bank::report() {
    StatisticsKeeper::instance()->report();
}
