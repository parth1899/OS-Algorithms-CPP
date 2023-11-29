#include<iostream>
#include<vector>
#include<cstdint>
using namespace std;

struct process{
    int id;
    int priority;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    int response;
    bool completed;


    // process(int _id, int _priority, int _arrival, int _burst) : id(_id), priority(_priority), arrival(_arrival),
    // burst(_burst), waiting(0), turnaround(0), response(-1), completed(false) {}
};

void priority_np(vector<process> &processes){
    int currenttime = 0;
    int completed_processes = 0;
    int max_priority;
    process* currproc = NULL;

    while(completed_processes < processes.size()){
        max_priority = INT32_MAX;
        for(int i = 0; i < processes.size(); i++){
            if(!processes[i].completed && max_priority > processes[i].priority && processes[i].arrival <= currenttime){
                max_priority = processes[i].priority;
                currproc = &processes[i];
            }
        }

        if(currproc == NULL){
            currenttime++;
        }
        else{
            if(currproc->response == -1)
                currproc->response = currenttime;

            currenttime += currproc->burst;
            currproc->completion = currenttime;
            currproc->turnaround = currenttime - currproc->arrival;
            currproc->waiting = currproc->turnaround - currproc->burst;
            currproc->completed = true;
            completed_processes++;
        }
    }

    cout << "Id\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(process &p : processes){
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t"
        << p.turnaround << "\t" << p.waiting << "\t" << p.response << "\n";
    }      
}


int main(){
    int n;
    cout << "Number of processes: ";
    cin >> n;

    vector<process> processes(n);
    //processes.reserve(n);

    int arr, burst, priority;
    for(int i = 0; i < n; i++){
        cout << "Enter arrival ,burst and priority for process " << i << " : ";
        cin >> arr >> burst >>  priority;
        processes.emplace_back(i,priority,arr,burst);

        std::cout << "Enter process " << i << " arrival time: ";
        cin >> arr;
        std::cout << "Enter process " << i << " burst time: ";
        cin >> burst;
        std::cout << "Enter process " << i << " priority: ";
        cin >> priority;
        //processes.emplace_back(i,arr,burst);
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].priority = priority;
        processes[i].id = i;
        processes[i].completed = false;
        processes[i].response = -1;
    }

    priority_np(processes);
}
