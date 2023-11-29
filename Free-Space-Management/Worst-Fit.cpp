#include <iostream>

using namespace std;

struct Block
{
    int size;
    bool allocated;
};

void worstFit(Block *memory, int numBlocks, int processSize)
{
    int worstFitIndex = -1;
    int maxSize = 0;

    for (int i = 0; i < numBlocks; ++i)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size > maxSize)
            {
                maxSize = memory[i].size;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1)
    {
        memory[worstFitIndex].allocated = true;
        cout << "Process allocated to Block " << worstFitIndex + 1 << endl;
    }
    else
    {
        cout << "No suitable block found for the process." << endl;
    }
}

int main()
{
    int numBlocks;

    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;

    Block *memory = new Block[numBlocks];
    for (int i = 0; i < numBlocks; ++i)
    {
        cout << "Enter the size of Block " << i + 1 << ": ";
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; ++i)
    {
        int processSize;
        cout << "Enter the size of Process " << i + 1 << ": ";
        cin >> processSize;
        worstFit(memory, numBlocks, processSize);
    }
    delete[] memory;

    return 0;
}
