#include<iostream>
#include<vector>
#include<unordered_map>
#include "process.h"
using namespace std;

/**
 * Implementation of class Process_creator to create process with random arrival & burst time
 
    * Attribute - 
         * simul_t {total simulation time}
         * n_processes {total number of processes to create}
         * burst_time_limit {Max CPU burst time for each process}
            * burst_time_limit = 0 (default value), implies Max CPU burst time for each process equals to max remaining time. 
    * Methods -
        * int arrival_gen(int) {Genrates random value for process arrival time}
        * int burst_gen(int) {Genrates random value for process burst time}
        * void creator(void)  {creator process with random burst&arrival time}
 */
class Process_Creator{
    
    public:
        int simul_t;
        int n_processes;
        int burst_time_limit;
        unordered_map<int,Process> &process;

        


        /**
         * @brief Construct a new Process_Creator object
         * 
         * @param t {total simulation time in seconds}
         * @param n {total number of processes}
         * @param pr {refrence to unordered_map<int,Process> }
         * @param b {burst time limit for single process}
         */
        Process_Creator(float t, int n, unordered_map<int,Process> &pr, int b = 0 )
        : simul_t(t), n_processes(n),process(pr), burst_time_limit(b){
            creator();
            cout << "All process initialized successfully!"<<endl;
        }

        // Generates random arrival time between (0 - simul_t*1000)
        int arrival_gen(){
            srand(clock());
            int x = rand();    // rand (), returns a pseudo-random number in the range of [0, RAND_MAX)
            return x%(simul_t-1);
        }


        // Generates random Burst time in range(1 - burst_time_limit)
        int burst_gen(int arr_t){
            srand(clock());
            int x = rand();
            if(burst_time_limit == 0){
                // default limit = max remaining simul_time
                int time_remain = simul_t - arr_t;
                return x%(time_remain-1)?x%(time_remain-1):1;
            }
            else{
                return x%(burst_time_limit)?x%(burst_time_limit):1;
            }
        }


        /**
         * @brief void creator(void), creates process.
         */
        void creator(){

            for(int i=0;i<n_processes;i++){
                int arrival_time = arrival_gen();
                int burst_time = burst_gen(arrival_time);
                process[i] = Process(i,arrival_time, burst_time);
                process[i].show_info();
                
            };
        }

};
