#include <iostream>
#include <vector>
#include <algorithm> // for std::sort
using namespace std;

struct Process {
    int id;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
    bool completed;
};

void fcfs(vector<Process> &processes){
    int currenttime {0};
   for(int i = 0; i < processes.size(); i++){
        Process* currentProc = &processes[i];
        for(int j = 0; j < processes.size(); j++){
            if(processes[j].arrivaltime <= currenttime && !processes[j].completed && currentProc->arrivaltime > processes[j].arrivaltime){
                currentProc = &processes[j];
            }
        }
        if(currenttime < currentProc->arrivaltime)
            currenttime = currentProc->arrivaltime;

        currenttime += currentProc->bursttime;
        currentProc->completiontime = currenttime;
        currentProc->turnaroundtime = currenttime - currentProc->arrivaltime;
        currentProc->waitingtime = currentProc->turnaroundtime - currentProc->bursttime;
        currentProc->completed = true;

        cout << "Process id: " << currentProc->id << endl
             << "Process arr: " << currentProc->arrivaltime << endl
             << "Process burst: " << currentProc->bursttime << endl
             << "Process completion: " << currentProc->completiontime << endl
             << "Process turnaround: " << currentProc->turnaroundtime << endl
             << "Process waiting: " << currentProc->waitingtime << endl << endl;
    }   
}

int main() {
    int n;
    float AverageWT = 0;
    float AverageTAT = 0;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter arrival times and burst times for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> processes[i].arrivaltime;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].bursttime;
        processes[i].completed = false;
    }
    // Perform FCFS scheduling
    fcfs(processes);

    // Display the scheduling results
    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (Process& process : processes) {
        AverageWT += process.waitingtime;
        AverageTAT += process.turnaroundtime;

        cout << process.id << "\t" << process.arrivaltime << "\t\t" << process.bursttime << "\t\t"
             << process.completiontime << "\t\t" << process.turnaroundtime << "\t\t" << process.waitingtime << "\n";
    }

    cout << "\nAverage Waiting Time is " << AverageWT / n << "\n";
    cout << "Average Turnaround Time is " << AverageTAT / n << "\n";
    return 0;
}

