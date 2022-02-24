
#include<iostream>
using namespace std;



/**
 * Implementation of class Process having following -
    * Attributes -
        * Private - 
            * pid {process Id}
            * arv_t {Process Arrival Time}
        * Public -
            * brst_t {Process CPU Burst Time}
            * comp_t {Process Completion time}
            * trn_arnd_t {Process Turn Around Time}
            * wait_t {Process Waiting Time}
            * resp_t {Process Respose Time} 

    * Methods -
        * show_info() {shows detailed info about process in same order as above attributes order}
        * get_pid()  {return process Id}
        * get_arv_t() {return process arrival time}
        
 */
class Process{
    private:
        int pid, arv_t,brst_t;

    public: 
        
        int comp_t=-1, trn_arnd_t=-1, wait_t=-1, resp_t=-1, rem_brst_t;

        Process(){
            pid = 0;
            arv_t = 0;
            brst_t = 0;
        }

        Process(int process_id, int arrival_time, int burst_t)
        :pid(process_id), arv_t(arrival_time), brst_t(burst_t), rem_brst_t(burst_t){}

        int get_pid(){
            return pid;
        }
        int get_arv_t(){
            return arv_t;
        }
        int get_brst_t(){
            return brst_t;
        }


        
        void show_info(){
            
            printf("[%3d %4d %4d %4d %3d %3d %3d %3d ]\n", pid, arv_t, brst_t, comp_t, trn_arnd_t, wait_t, resp_t, rem_brst_t);
        }

};



