#include "ATM.h"
#include "StatisticsKeeper.h"
#include "TrafficGenerator.h"
#include "Transaction.h"
#include "Customer.h"

ATM::ATM(int id) {
    this->id = id;
    this->money = INITIALMONEY;
}

void ATM::insert_customer(Customer* customer) {
    queue.push_back(customer);
}
void ATM::display() {
    std::cout << "ATM" << id;
    for (std::list<Customer*>::const_iterator iter = queue.begin(); iter != queue.end(); ++iter) {
        Customer* cc = *iter;
        cc->display();
        std::cout << " ";
    }
    std::cout << "|";
}
int ATM::dequeue(int time_slot) {
    if(queue.size() == 0) {
        std::cout << "empty queue" << std::endl; 
    }
    Customer* customer = *(queue.begin());
    Transaction* transaction = customer->get_transaction();
    if (transaction->get_transtype() == DEPOSIT) {
        this->money += transaction->get_transaction_money();
    }
    else if (transaction->get_transtype() == WITHDRAWAL) {
        this->money -= transaction->get_transaction_money();
        if (this->money <= 100) {
            this->money = INITIALMONEY;
            StatisticsKeeper::instance()->add_atm_refill();
        }
    }
    
    customer->set_exit_time(time_slot);
    //std::cout << "arrive:" << customer->get_arrival_time() << " service:" << customer->get_service_time() << " exit:" << customer->get_exit_time();
    StatisticsKeeper::instance()->add_customer(customer);
    customer->report_done();
    TrafficGenerator::instance()->reuse(customer);
    queue.pop_front();
    if (queue.empty()) {
        return -1;
    }
    customer = *(queue.begin());
    return customer->get_service_time();
}

int ATM::customers() {
    return queue.size();
}

