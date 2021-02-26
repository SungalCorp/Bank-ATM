#include <iostream>
#include <string>
#include "Bank.h"
using namespace std;

// simulation time, input and output file name,
void get_user_input(string& fname, int& atms, int& sim_time) {
    cout << "Please specify input file name:\n";
    cin >> fname;

    cout << "Number of ATMs:\n";
    cin >> atms;

    cout << "Simulation time:\n";
    cin >> sim_time;
}

void finish() {
    cout << endl << "Please press Q to exit: " << endl;
    string s;
    cin >> s;
}

int main()
{
    Bank mybank;
    int ATMs, time;
    string fname;
    get_user_input(fname, ATMs, time);
    mybank.set_inputfile(fname);
    mybank.set_atm_num(ATMs);
    mybank.set_sim_time(time);

    mybank.generate_customerbase(); // Traffic Generator
    mybank.generate_initial_traffic(); // Traffic Generator

    mybank.simulate(); // System Controller
    mybank.report(); // Statistic Keeper

    finish();
}
