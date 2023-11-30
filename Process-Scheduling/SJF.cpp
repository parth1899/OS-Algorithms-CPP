#include<iostream>
#include<cstdint>
#include<vector>
#include<algorithm>
using namespace std;

struct process{
    int id;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    bool completed;

    //constructor for process
    // process(int _id, int _arrival, int _burst) : id(_id) ,arrival(_arrival), burst(_burst)
    // , completed(false) {}
};


int sjf(vector<process> &processes){
    int currenttime = 0;
    int countComplete = 0;
    process* currentproc = NULL;
    int min_burst;
    //std::cout << "hi3" << endl;
    while(countComplete < processes.size()){
        min_burst = INT32_MAX;
        for(int j = 0; j < processes.size(); j++){
            if(processes[j].arrival <= currenttime && min_burst > processes[j].burst && !processes[j].completed){
                min_burst = processes[j].burst;
                currentproc = &processes[j];
            }
        }
        // if (currentproc == NULL)
        // {
        //     currenttime++;
        // }
        //currenttime++;
        //std::cout << "hiloop" << endl;

        if (currentproc == NULL) //stalling
        {
            currenttime++;
        }
        else
        {
            if(currenttime < currentproc->arrival)
                currenttime = currentproc->arrival;
            
            currenttime += currentproc->burst;
            currentproc->completion = currenttime;
            currentproc->turnaround = currenttime - currentproc->arrival;
            currentproc->waiting = currentproc->turnaround - currentproc->burst;
            currentproc->completed = true;
            countComplete++;
            }

    }

    //std::cout << "hi4" << endl;

    std::cout << "Id\tAT\tBT\tCT\tTAT\tWT\n";
    for(process &p : processes){
        std::cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t"
        << p.turnaround << "\t" << p.waiting << "\n";
    }
    return 0;
}

int main(){

    int n;
    std::cout << "Enter num of processes: ";
    cin >> n;

    vector<process> processes(n);
    //processes.reserve(n);

    //std::cout << "hi1" << endl;

    int arr, burst;
    for(int i = 0; i < n; i++){
        std::cout << "Enter process " << i << " arrival time: ";
        cin >> arr;
        std::cout << "Enter process " << i << " burst time: ";
        cin >> burst;
        //processes.emplace_back(i,arr,burst);
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].id = i;
        processes[i].completed = false;
    }

    //  std::cout << "hi2" << endl;
    sjf(processes);
}

