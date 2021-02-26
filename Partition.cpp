#include "Partition.h"
#include <cstddef>

Partition::Partition() {
    atmp = NULL;
    nextp = NULL;
}
Partition::Partition(ATM* atmp, Partition* next) {
    this->atmp = atmp;
    this->nextp = next;
}
Partition* Partition::next() {
    return nextp;
}
ATM* Partition::get_ATM() {
    return atmp;
}
