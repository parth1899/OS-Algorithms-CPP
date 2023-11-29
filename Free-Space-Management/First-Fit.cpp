#include <iostream>
using namespace std;

struct Block
{
    int size;
    bool allocated;
};


void firstFit(Block *memory, int numBlocks, int processSize)
{
    for (int i = 0; i < numBlocks; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = true;
            cout << "Process allocated to Block " << i+1 << endl;
            return;
        }
    }

    cout << "No suitable block found for the process";
}

int main()
{
    int numBlocks; //number of blocks in main memory
    cout << "Enter number of blocks in the memory: ";
    cin >> numBlocks;

    Block* memory = new Block[numBlocks];

    for (int i = 0; i < numBlocks; i++)
    {
        cout << "Enter size of block " << i+1 << ": ";
        cin >> memory[i].size;
        memory[i].allocated = false;
    }

    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; i++)
    {
        int processSize;
        cout << "Enter the size of Process " << i+1 << ": ";
        cin >> processSize;
        firstFit(memory, numBlocks, processSize);   
    }

    delete[] memory;

    return 0;
}
