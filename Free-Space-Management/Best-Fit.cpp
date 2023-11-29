#include <iostream>
#include <limits.h>
using namespace std;

struct Block
{
    int size;
    bool allocated;
};

void bestFit(Block *memory, int numBlocks, int processSize)
{
    int bestFitIndex = -1;
    int minSize = INT_MAX;

    for (int i = 0; i < numBlocks; ++i)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size < minSize)
            {
                minSize = memory[i].size;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1)
    {
        memory[bestFitIndex].allocated = true;
        cout << "Process allocated to Block " << bestFitIndex + 1 << endl;
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
        bestFit(memory, numBlocks, processSize);
    }
    delete[] memory;

    return 0;
}
