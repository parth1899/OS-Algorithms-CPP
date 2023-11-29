#include <iostream>
#include <vector>
#include <cmath> //for abs()
using namespace std;

int fcfs_diskScheduling(vector<int>& requests, int initial_Position)
{
    int total_seek_time = 0;
    int current_Position = initial_Position;

    for (int request : requests)
    {
        int seek_distance = abs(request - current_Position);
        total_seek_time += seek_distance;
        current_Position = request;
    }   

    return total_seek_time;
}

int main()
{
    int n;
    cout << "Enter the number of Requests you want in the Request Queue: ";
    cin >> n;

    vector<int> requests(n);
    
    int track;
    for (int i = 0; i < n; i++)
    {
        cin >> track;
        requests[i] = track;
    }

    int initial_Position;
    cout << "Enter the initial position of head: ";
    cin >> initial_Position;    

    int seek_time = fcfs_diskScheduling(requests, initial_Position);

    cout << "The total seek time using FCFS is: " << seek_time << endl;

    return 0;
}
