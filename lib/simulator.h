#include "sched.h"

#include "define.h"
#include "sched_algo.h"

#include <fcntl.h>
#include <unistd.h>
#include<fstream>

class Simulator{
    private:
        int sched_algo;
        int simul_t;  // milli secs
        int n_processes;
        int burst_time_limit; //milli secs
        int t_q=1;
        
        
        
    public:
        unordered_map<int,Process> process;
        

        Simulator(int alg, int sim_t, int no_of_processes, int burst_limit=0, int time_q=1 )
        :sched_algo(alg), simul_t(sim_t), n_processes(no_of_processes),burst_time_limit(burst_limit),t_q(time_q){
            Process_Creator Creater(simul_t, n_processes, process, burst_time_limit);
                        
        }

       
        

        void run(){
            ofstream fout;
            fout.open("sec_status.txt");
            Scheduler sch(process,sched_algo,t_q);

            int Q ;
            int t=0;
           
            do{
                int r_pid = sch.process_to_run(t);
                Q = sch.time_quanta(r_pid);
               // cout << "call" << t <<"\n";
                if(r_pid<0){
                    // No Process in ready Queue
                    t++;
                    continue;
                }
                else{

                    //cout << r_pid <<" : "<< process[r_pid].rem_brst_t<< ", time: "<< t <<"\n";
                    
                    // response time
                    if(process[r_pid].rem_brst_t == process[r_pid].get_brst_t()){
                        process[r_pid].resp_t = t - process[r_pid].get_arv_t();
                    }
                    fout <<t <<"-  process" <<r_pid << "  : running"<<endl;

                    Q = min(Q, process[r_pid].rem_brst_t);
                    Q = min(simul_t - t, Q);
                    
                    // remaining cpu burst time
                    process[r_pid].rem_brst_t -= Q;

                    // completion time
                    if(process[r_pid].rem_brst_t == 0){

                        process[r_pid].comp_t = t+Q;
                        fout <<t+Q <<"-  process" <<r_pid << "  : completed"<<endl;
                    }

                    // time increment
                    
                    t = t +Q;
                }
            }while(t<simul_t);
        }


        void evaluate_all_info(){
            for (int pid=0;pid<n_processes;pid++){
                if(process[pid].rem_brst_t ==0 ){
                    process[pid].trn_arnd_t = process[pid].comp_t - process[pid].get_arv_t();
                    process[pid].wait_t = process[pid].trn_arnd_t - process[pid].get_brst_t();
                }
            }
        }

        void info_print(){
            evaluate_all_info();
            printf("\n pid arv  brt  c_t tAt w_t rsp_t r_bt : Table Column Order\n\n");
            for (int pid=0;pid<n_processes;pid++){
                process[pid].show_info();
            }
        }

        void put_in_file(){
            evaluate_all_info();
            int fd = open("Process_info.txt", O_RDWR| O_CREAT);
            dup2(fd,1);
            info_print();
        }

};



