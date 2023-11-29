#include <iostream>
#include <cmath>

using namespace std;
const int PAGE_SIZE = 4096;
int logicalToPhysical(int logicalAddress, int pageTable[], int pageTableSize, int pageSize)
{
    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;
    if (pageNumber >= 0 && pageNumber < pageTableSize && pageTable[pageNumber] != -1)
    {
        int frameNumber = pageTable[pageNumber];
        int physicalAddress = frameNumber * pageSize + offset;
        return physicalAddress;
    }
    else
    {
        cout << "Page fault: Page " << pageNumber << " not in memory." << endl;
        return -1;
    }
}

int main()
{
    int pageTable[] = {1, 0, -1, 2};
    int pageTableSize = sizeof(pageTable) / sizeof(pageTable[0]);
    int logicalAddress;
    cout << "Enter a logical address: ";
    cin >> logicalAddress;
    int physicalAddress = logicalToPhysical(logicalAddress, pageTable, pageTableSize, PAGE_SIZE);
    if (physicalAddress != -1)
    {
        cout << "Physical Address: " << physicalAddress << endl;
    }

    return 0;
}
