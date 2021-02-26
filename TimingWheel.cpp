#include "TimingWheel.h"
#include "ATM.h"
#include "Partition.h"
#include<iostream>

using namespace std;
TimingWheel* TimingWheel::m_instance = NULL;

TimingWheel* TimingWheel::instance() {
    if (m_instance == NULL) {
        m_instance = new TimingWheel();
    }
    return m_instance;
}

TimingWheel::TimingWheel() {
    for (int i = 0; i < max_delay + 1; ++i) {
        slot[i] = NULL;
    }
    current_slot = 0; //
}

void TimingWheel::insert(int customer_service_time, ATM* p1) {
    int index = (current_slot + customer_service_time) % (max_delay + 1);
    Partition* partition = new Partition(p1, slot[index]);
    slot[index] = partition;
}

void TimingWheel::display() {
    std::cout << "---------" << std::endl;
    for (int i = 0; i < max_delay + 1; ++i) {
        std::cout << "slot[" << i << "] ";
        Partition* p = slot[i];
        while (p != NULL) {
            ATM* atmp = p->get_ATM();
            atmp->display();
            p = p->next();
        }
        std::cout << std::endl;
    }
    std::cout << "---------" << std::endl;
}
void TimingWheel::schedule() {
    if (current_slot == 0) {
        current_slot = 1;
        return;
    }
    ++current_slot;
    //current_slot %= (max_delay + 1);
    //std::cout << "schedule" << current_slot << std::endl;

    //new add partion will not in current_slot
    for (Partition* partition = slot[current_slot % (max_delay + 1)]; partition != NULL;) {
        ATM* atm = partition->get_ATM();
        int service_time = atm->dequeue(current_slot);
        if (service_time > 0) {
            int new_slot_index = (current_slot + service_time) % (max_delay + 1);
            Partition* new_partition = new Partition(atm, slot[new_slot_index]);
            slot[new_slot_index] = new_partition;
        }
        //cout << "***" << partition->get_ATM->customer->get_id() << " " << customer->get_service_time() << endl;
        cout << partition->get_ATM() << "is now available" << endl;
        Partition* next_partition = partition->next();
       
        delete partition;
        partition = next_partition;
    }
    slot[current_slot % (max_delay + 1)] = NULL;
    //for all partitions in current slot, delete it, and insert the sencond one
    /////////////
    //std::cout << "current_slot:" << current_slot << " index:" << (current_slot % (max_delay + 1))<< std::endl;
    //display();
}
