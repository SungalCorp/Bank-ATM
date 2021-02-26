#include "Customer.h"
#include "Account.h"
#include "Transaction.h"

Customer::Customer() {
    id = UniqID::instance()->genID("customer");
    arrival_time = -1;
    service_time = -1;
    exit_time = -1;
    transaction = NULL;
}
Customer::~Customer() {
    for (unsigned i = 0; i < accounts.size(); ++i) {
        delete accounts[i];
    }
    accounts.clear();
}
void Customer::set_service_time(int time) {
    service_time = time;
}

void Customer::set_arrival_time(int time) {
    arrival_time = time;
}
void Customer::set_exit_time(int time) {
    exit_time = time;
}

void Customer::add_account(Account* account) {
    accounts.push_back(account);
}
int Customer::get_id() {
    return id;
}
int Customer::get_service_time() {
    return service_time;
}

int Customer::get_arrival_time() {
    return arrival_time;
}
int Customer::get_exit_time() {
    return exit_time;
}
void Customer::display() {
    // todo with other account type  accounts
    /*if(accounts.size() == 0) {
        return;
    }*/
    std::cout << "(" << id << " " << this->transaction->get_initiator_account()->id() << " arr:" << arrival_time << " ser:" << service_time << ")";
    //std::cout << "(" << id << "," << accounts[0]->id() << " arr:" << arrival_time << " ser:" << service_time << ")";
}

std::vector<Account*>& Customer::get_accounts() {
    return accounts;
}

void Customer::report_done() {
    this->transaction->get_initiator_account()->report_done();
    delete this->transaction;
    this->transaction = NULL;
}

Account* Customer::get_curr_account() {
    return this->transaction->get_initiator_account();
}

void Customer::set_transaction(Transaction* transaction) {
    this->transaction = transaction;
}

Transaction* Customer::get_transaction() {
    return this->transaction;
}
