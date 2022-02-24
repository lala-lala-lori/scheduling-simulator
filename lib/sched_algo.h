#include "process_creator.h"

#include "define.h"
#include<algorithm>
#include<vector>
#include<queue>
 #include<fstream>




namespace Fcfs{
    class FcfsComp{
    public: 
        bool operator()(Process &p1, Process &p2){
            if(p1.get_arv_t() > p2.get_arv_t()){
                return true;
            }
            else if(p1.get_arv_t() == p2.get_arv_t()){
                return p1.get_pid()>p2.get_pid();
            }
            else{
                return false;
            }
        }
    };


    int schedule(unordered_map<int, Process> &process, priority_queue<Process, vector<Process> , FcfsComp > &pq){
        for( auto i: process){
            pq.push(i.second);
        }
        return 0;
    }

    int process_to_run(priority_queue<Process, vector<Process> , FcfsComp > &pq, int t){
        if(!pq.empty()){
            Process p1 = pq.top();
            //cout << "arrvt: "<<p1.get_arv_t()<<" "<<t <<"\n";
            if(p1.get_arv_t() <= t){
                pq.pop();
                return p1.get_pid();
            }
        }
        return -1;
    } 
}

namespace Srtf{
    class SrtfComp{
        public:
            bool operator()(Process &p1, Process &p2){
                if(p1.rem_brst_t > p2.rem_brst_t){
                    return true;
                }
                else if(p1.rem_brst_t == p2.rem_brst_t){
                    return p1.get_pid()>p2.get_pid();
                }
                else{
                    return false;
                }
            }

    };

    


    int process_to_run(unordered_map<int, Process> &process, priority_queue<Process, vector<Process> , SrtfComp > &pq, vector<Process> &sorted_pr, int time){
        // Scheduled Queue
        for(auto ps: sorted_pr){
            if( time >= ps.get_arv_t()){
                if(process[ps.get_pid()].rem_brst_t > 0){
                    pq.push(ps);}
            }
            else{
                break;
            }
        }
    
        if(!pq.empty()){
            Process p1 = pq.top();
            // cout <<p1.get_pid() <<": "<< p1.rem_brst_t <<" \n ";
            pq.pop();
            return p1.get_pid();
        }
        else{ 
            return -1;
        }
    }

}

namespace RR{

   
    int process_to_run(unordered_map<int, Process> &process, queue<int>&Q, vector<Process> &sorted_pr, int time){
        
        for( auto ps: sorted_pr){
            if( time >= ps.get_arv_t() ){
                if(process[ps.get_pid()].rem_brst_t > 0){
                    Q.push(ps.get_pid());
                   
                    // ofstream fout;
                    // fout.open("sec_status.txt", ios::app);
                    // fout <<time<<"-  process"<<ps.get_pid() <<"  : arrived\n";
                    
                   
                    sorted_pr.erase(sorted_pr.begin());
                }
            }
            else{
                break;
            }
        }


        if(!Q.empty()){
            int pid = Q.front();
            
            if(process[pid].get_arv_t() <= time){
                //cout << "arrvt: "<<p1.get_arv_t()<<" "<<t <<"\n";
                Q.pop();
                if(process[pid].rem_brst_t > 0)
                    Q.push(pid);
                if(process[pid].rem_brst_t <= 0)
                    return -1;
                return pid;
            }
        }
        return -1;
    } 

}



bool sortComp(Process &p1, Process &p2){
    if(p1.get_arv_t() < p2.get_arv_t()){
        return true;
    }
    else if(p1.get_arv_t() == p2.get_arv_t()){
        return p1.get_pid()<p2.get_pid();
    }
    else{
        return false;
    }
}

class Scheduler{
    private:
        int sched_algo;
        int rr_Qt;
        
    public:
        unordered_map<int, Process>&process;
        vector<Process> sorted_pr;  // sorted process by arrival time & pid

        Scheduler(unordered_map<int, Process>&pr):sched_algo(SCHED_FCFS),process(pr){}

        Scheduler(unordered_map<int, Process>&pr, int alg, int rr_tq=1)
        : process(pr), sched_algo(alg), rr_Qt(rr_tq){

            // Sorting process with arrival time & pid
            for(auto x: process){
                sorted_pr.push_back(x.second);
            }
            sort(sorted_pr.begin(),sorted_pr.end(),sortComp);
            Process P1 = sorted_pr.front(); 
            
        }

        int time_quanta(int pid){
            if(pid<0){
                return 0;
            }
            if(sched_algo == SCHED_FCFS){
                // non-preemptive
                return process[pid].get_brst_t();
            }
            else if(sched_algo == SCHED_SRTF){
                // preemptive
                return 1;
            }
            else{
                // Round Robin
                return rr_Qt;
            }
        }



        int process_to_run(int time){
            if(sched_algo ==  SCHED_FCFS){
               // cout << "$ USING FCFS\n";
                static priority_queue<Process, vector<Process> ,Fcfs::FcfsComp > pq; 
                static int x = Fcfs::schedule(process,pq);
                int pid = Fcfs::process_to_run(pq,time);
                return pid;
            }
            else if(sched_algo == SCHED_SRTF){

                priority_queue<Process, vector<Process> ,Srtf::SrtfComp > pq; 
                
                int pid = Srtf::process_to_run(process, pq, sorted_pr, time);
                return pid;
            }
            else if(sched_algo == SCHED_RR){
                
                static queue<int> Q;
                int pid  = RR::process_to_run(process, Q, sorted_pr, time);
                return pid;
            }
            else{
                cout <<"Scheduling Algo not exists !";
                return -1;
            }
            
        }


};

