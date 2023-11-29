#include <iostream>

using namespace std;

struct Block
{
    int size;
    bool allocated;
};

void nextFit(Block *memory, int numBlocks, int processSize, int &lastAllocated)
{
    int startIndex = lastAllocated;

    do
    {
        if (!memory[startIndex].allocated && memory[startIndex].size >= processSize)
        {
            memory[startIndex].allocated = true;
            cout << "Process allocated to Block " << startIndex + 1 << endl;
            lastAllocated = (startIndex + 1) % numBlocks;
            return;
        }

        startIndex = (startIndex + 1) % numBlocks;
    } while (startIndex != lastAllocated);
    cout << "No suitable block found for the process." << endl;
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
    int lastAllocated = 0;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i)
    {
        int processSize;
        cout << "Enter the size of Process " << i + 1 << ": ";
        cin >> processSize;
        nextFit(memory, numBlocks, processSize, lastAllocated);
    }
    delete[] memory;

    return 0;
}
