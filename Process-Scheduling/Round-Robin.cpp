#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct process{
    int id;
    int arrival;  
    int burst;
    int completion;
    int remaining;
    int waiting;
    int turnaround;
    int response;
    bool inreadyQ;
    bool completed;

    process(int _id, int _arrival, int _burst) : id(_id), arrival(_arrival), burst(_burst), remaining(_burst), 
    waiting(0), turnaround(0), response(-1),inreadyQ(false), completed(false) {}
};

void round_robin(vector<process> &processes){
    queue<process*> readyQ;
    int currenttime = 0;
    int time_quantum;
    cout << "Enter time quantum: ";
    cin >> time_quantum;
    int completedproc = 0;
    process* currentprocess = NULL;

    for(int i = 0; i < processes.size(); i++){
        if(!processes[i].completed && currenttime >= processes[i].arrival && !processes[i].inreadyQ){
            readyQ.push(&processes[i]);
            processes[i].inreadyQ = true;
        }
    }
    while(completedproc < processes.size()){
        currentprocess = readyQ.front();
        readyQ.pop();  //deletes first element of the queue

        if(currentprocess->response == -1)
            currentprocess->response = currenttime - currentprocess->arrival;

        currenttime += min(currentprocess->remaining, time_quantum);
        currentprocess->remaining -= min(currentprocess->remaining, time_quantum);

        for(int i = 0; i < processes.size(); i++){
            if(!processes[i].completed && currenttime >= processes[i].arrival && !processes[i].inreadyQ){
                readyQ.push(&processes[i]);
                processes[i].inreadyQ = true;
            }
        }

        if(currentprocess->remaining > 0)
            readyQ.push(currentprocess);
        else{
            completedproc++;
            currentprocess->completion = currenttime;
            currentprocess->turnaround = currenttime - currentprocess->arrival;
            currentprocess->waiting = currentprocess->turnaround - currentprocess->burst;
            currentprocess->completed = true;
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

    vector<process> processes;
    processes.reserve(n);

    int arr, burst;
    for(int i = 0; i < n; i++){
        cout << "Enter arrival and burst for process " << i << " : ";
        cin >> arr >> burst;
        processes.emplace_back(i,arr,burst);
    }

    round_robin(processes);
}
