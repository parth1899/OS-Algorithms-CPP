#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

struct process
{
    int id, priority, at, bt, ct, wt, tat, rt, remaining;
    bool completed;

    process(int _id, int _priority, int _at, int _bt) : id(_id), priority(_priority), at(_at), bt(_bt), ct(0), wt(0), tat(0), rt(-1), remaining(_bt), completed(false) {}
};

void priority_premp(vector<process>& processes)
{
    int currentTime = INT32_MAX;

    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i].at < currentTime)
        {
            currentTime = processes[i].at;
        }
    }

    int completedProcesses = 0;
    process * currentProcess;
    int maxPriority = INT32_MAX;


    while (completedProcesses < processes.size())
    {
        currentProcess = NULL; //do this every iteration cuz its preemptive
        maxPriority = INT32_MAX;

        for (int i = 0; i < processes.size(); i++)
        {
            if (!processes[i].completed && processes[i].at <= currentTime && maxPriority >= processes[i].priority)
            {
                maxPriority = processes[i].priority;
                currentProcess = &processes[i];
            }
        }

        if (currentProcess ==  NULL)
        {
            currentTime++;
        }
        else
        {
            if (currentProcess->rt == -1)
            {
                currentProcess->rt == currentTime - currentProcess->at; //NOT WORKING
            }

            currentTime++; //doubtful

            if (currentProcess->remaining > 0)
            {
                currentProcess->remaining--;

                if (currentProcess->remaining == 0)
                {
                    currentProcess->ct = currentTime;
                    currentProcess->tat = currentTime - currentProcess->at;
                    currentProcess->wt = currentProcess->tat - currentProcess->bt;
                    currentProcess->completed = true;
                    completedProcesses++;
                }
            }
        }
    }

    cout << "Id\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(process&p : processes)
    {
        cout << p.id <<"\t" << p.at <<"\t"  << p.bt<<"\t"   << p.ct<<"\t"  << p.tat<<"\t"  << p.wt<<"\t"  << p.rt << "\n";
    }

}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<process> processes;
    processes.reserve(n);

    int arrival, burst, priority;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the Priority, Arrival Time and Burst Time for Process " << i+1 << " : ";
        cin >> priority >> arrival >> burst;
        processes.emplace_back(i, priority, arrival, burst);
    }

    priority_premp(processes);

    return 0;
}
