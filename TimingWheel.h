#ifndef __TimingWheel_H
#define __TimingWheel_H

class Partition;
class ATM;
#define max_delay 12 //max customer transaction time possible

class TimingWheel
{
public:
    static TimingWheel* instance();
    //insert a partition in the timing wheel with the appropriate delay
    void insert(int customer_service_time, ATM* p1);
    /**
     * update the statistics of the customer leaving
     * dequeue customer form the ATM(s) and insert the next customer in queue through
     * appropriate ATM Controller System components
     *
     * */
    void schedule();
    void display();
private:
    static TimingWheel* m_instance;
    TimingWheel();
    //insert a partition in the timing wheel with the appropriate delay
    Partition* slot[max_delay + 1];
    //slot[current_slot] finish work now
    int current_slot;
};

#endif
