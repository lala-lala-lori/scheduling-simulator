#include "./lib/simulator.h"

int main(int argc, char *argv[]){

    int sched_algo = SCHED_RR;
    int simul_t = 100;
    int n_processes = 10;
    int burst_limit = 12;
    int rr_t = 2;

    // cout << "scheduling algo: ";
    // cin >> sched_algo;
    // cout << "simulation time: ";
    // cin >> simul_t;
    // cout << "no.of processes: ";
    // cin >> n_processes;
    // cout << "cpu burst limit: ";
    // cin >> burst_limit;

    Simulator sm(sched_algo,simul_t,n_processes,burst_limit,rr_t);
    sm.run();
    sm.info_print();
    sm.put_in_file();


    // final values


    return 0;

    
}