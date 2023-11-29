#include<iostream>
#include<vector>
#include<cstdint>   
using namespace std;

struct process{
    int id;
    int arrival;
    int burst;
    int completion;
    int remaining;
    int waiting;
    int turnaround;
    bool completed;

    // process(int _id, int _arrival, int _burst) : id(_id), arrival(_arrival), burst(_burst), remaining(_burst), 
    // waiting(0), turnaround(0), completed(false) {}
};

void srtf(vector<process> &processes){
    int currenttime = 0;
    process* currentproc = NULL;
    int min_burst;
    int completed_processes = 0;

    while (completed_processes < processes.size()) {
        currentproc = NULL;
        int min_burst = INT32_MAX;

        for (int i = 0; i < processes.size(); i++) {
            if (!processes[i].completed && processes[i].remaining > 0 && processes[i].arrival <= currenttime) {
                if (processes[i].remaining < min_burst) {
                    min_burst = processes[i].remaining;
                    currentproc = &processes[i];
                }
            }
        }

        if (currentproc == NULL) {
            cout << "Idle(" << currenttime << " -> " << currenttime + 1 << ")\n";
            currenttime++;
        } else {
            currentproc->remaining--;
            currenttime++;

            if (currentproc->remaining == 0) {
                currentproc->completion = currenttime;
                currentproc->turnaround = currentproc->completion - currentproc->arrival;
                currentproc->waiting = currentproc->turnaround - currentproc->burst;
                currentproc->completed = true;
                completed_processes++;
            }
        }
    }

    int avgWT = 0;
    int avgTAT = 0;

    cout << "Id\tAT\tBT\tCT\tTAT\tWT\n";
    for(process &p : processes){
        avgWT+= p.waiting;
        avgTAT+= p.turnaround;
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion << "\t"
        << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << "AverageWT: " << avgWT/processes.size() << endl;
    cout << "AverageTAT: " << avgTAT/processes.size() << endl;
}

int main(){
    int n;
    cout << "Number of processes: ";
    cin >> n;

    vector<process> processes(n);
    //processes.reserve(n);

    int arr, burst;
    for(int i = 0; i < n; i++){
        std::cout << "Enter process " << i << " arrival time: ";
        cin >> arr;
        std::cout << "Enter process " << i << " burst time: ";
        cin >> burst;
        //processes.emplace_back(i,arr,burst);
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].remaining = burst;
        processes[i].id = i;
        processes[i].completed = false;
        //processes[i].waiting = 0;
    }

    srtf(processes);
}

