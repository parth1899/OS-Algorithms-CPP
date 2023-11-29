#include <iostream>
using namespace std;

bool isSafe(int process, int **max, int **allocation, int *available, int *work, bool *finish,
            int numResources)
{
    for (int i = 0; i < numResources; ++i)
    {
        if (max[process][i] - allocation[process][i] > work[i])
        {
            return false;
        }
    }

    return true;
}
void bankersAlgorithm(int **max, int **allocation, int *available, int numProcesses, int numResources)
{
    int *work = new int[numResources];
    bool *finish = new bool[numProcesses];
    int *safeSequence = new int[numProcesses];
    int safeSequenceIndex = 0;
    bool deadlockDetected = false;

    for (int i = 0; i < numResources; ++i)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < numProcesses; ++i)
    {
        finish[i] = false;
    }

    for (int k = 0; k < numProcesses; ++k)
    {
        for (int i = 0; i < numProcesses; ++i)
        {
            if (!finish[i] && isSafe(i, max, allocation, available, work, finish, numResources))
            {
                for (int j = 0; j < numResources; ++j)
                {
                    work[j] += allocation[i][j];
                }
                finish[i] = true;
                safeSequence[safeSequenceIndex++] = i;
                break;
            }
        }
    }
    for (int i = 0; i < numProcesses; ++i)
    {
        if (!finish[i])
        {
            deadlockDetected = true;
            break;
        }
    }
    if (deadlockDetected)
    {
        cout << "Deadlock Detected! System is in an unsafe state.\n";
    }
    else
    {
        cout << "System is in a safe state.\nSafe Sequence: ";
        for (int i = 0; i < numProcesses; ++i)
        {
            cout << "P" << safeSequence[i] << " ";
        }
        cout << endl;
    }
    delete[] work;
    delete[] finish;
    delete[] safeSequence;
}

int main()
{
    int numProcesses, numResources;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;
    int **max = new int *[numProcesses];
    for (int i = 0; i < numProcesses; ++i)
    {
        max[i] = new int[numResources];
    }
    int **allocation = new int *[numProcesses];
    for (int i = 0; i < numProcesses; ++i)
    {
        allocation[i] = new int[numResources];
    }
    int *available = new int[numResources];
    cout << "Enter the Maximum Resource Needs Matrix:\n";
    for (int i = 0; i < numProcesses; ++i)
    {
        for (int j = 0; j < numResources; ++j)
        {
            cout << "Max[" << i << "][" << j << "]: ";
            cin >> max[i][j];
        }
    }
    cout << "Enter the Allocation Matrix:\n";
    for (int i = 0; i < numProcesses; ++i)
    {
        for (int j = 0; j < numResources; ++j)
        {
            cout << "Allocation[" << i << "][" << j << "]: ";
            cin >> allocation[i][j];
        }
    }
    cout << "Enter the Available Resources Vector:\n";
    for (int i = 0; i < numResources; ++i)
    {
        cout << "Available[" << i << "]: ";
        cin >> available[i];
    }
    bankersAlgorithm(max, allocation, available, numProcesses, numResources);
    for (int i = 0; i < numProcesses; ++i)
    {
        delete[] max[i];
        delete[] allocation[i];
    }
    delete[] max;
    delete[] allocation;
    delete[] available;

    return 0;
}
