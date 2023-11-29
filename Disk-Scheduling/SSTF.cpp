#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>
#include <algorithm>


using namespace std;

int find_closest_request(vector<int>& requests, int current_Position)
{
    int min_Distance = INT32_MAX;
    int closest_Request = -1;


    for (int request : requests)
    {
        int seek_Distance = abs(request - current_Position);
        if (seek_Distance < min_Distance)
        {
            min_Distance = seek_Distance;
            closest_Request = request;
        }
    }

    return closest_Request;
}

int sstf(vector<int>& requests, int initial_Position)
{
    int total_seek_time = 0;
    int current_Position = initial_Position;

    while(!requests.empty())
    {
        int closest_Request = find_closest_request(requests, current_Position);
        int seek_distance = abs(closest_Request - current_Position);
        total_seek_time += seek_distance;
        current_Position = closest_Request;


        //remove the request which is done from the vector

        auto it = find(requests.begin(), requests.end(), closest_Request);
        if (it != requests.end())
        {
            requests.erase(it);
        }
    }

    return total_seek_time;
}

int main()
{
    int n;
    cout << "Enter the number of requests you want in the Request Queue: ";
    cin >> n;

    vector<int> requests(n);
    
    int track;
    for (int i = 0; i < n; i++)
    {
        cin >> track;
        requests[i] = track;
    }

    int initial_Position;
    cout << "Enter Initial Position: ";
    cin >> initial_Position;

    int seekTime = sstf(requests, initial_Position);
    cout << "The Total Seek Time is " << seekTime << endl;

    return 0;
}
