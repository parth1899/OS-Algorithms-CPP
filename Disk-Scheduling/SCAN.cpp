#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//refer to seek sequence code from gfg

int scan(vector<int> requests, int initial_Position, string direction, int track_size)
{
    int total_seek_time = 0;
    int current_Position = initial_Position;
    vector<int> left, right;

    //append the values depending on direction, if left then append 0, if right then append size-1
    if (direction == "left")
    {
        left.push_back(0);
    }
    else if (direction == "right")
    {
        right.push_back(track_size - 1);
    }


    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] < initial_Position)
        {
            left.push_back(requests[i]);
        }
        else
        {
            right.push_back(requests[i]);
        }
    }

    //sort left and right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    //run while loop twice
    int run = 2;
    while(run--)
    {
        if (direction == "left")
        {
            for (int i = left.size() - 1; i >= 0; i--)
            {
                int distance = abs(left[i] - current_Position);
                total_seek_time += distance;
                current_Position = left[i];
            }
            direction = "right";
        }

        else if (direction == "right")
        {
            for (int i = 0; i < right.size(); i++)
            {
                int distance = abs(right[i] - current_Position);
                total_seek_time += distance;
                current_Position = right[i];
            }
            direction = "left"; 
        }
        
    }

    return total_seek_time;

    

}

int main()
{
    int n;
    cout << "Enter the number of track requests you want: ";
    cin >> n;

    vector<int> requests(n);

    for (int i = 0; i < n; i++)
    {
        int ele;
        cin >> ele;
        requests[i] = ele;
    }

    int initial_Postion;
    cout << "Enter the Initial Position of the head: ";
    cin >> initial_Postion;

    string direction;
    cout << "Enter the direction: ";
    cin >> direction;

    int track_size;
    cout << "Enter the maximum number of tracks: ";
    cin >> track_size;

    int seekTime = scan(requests, initial_Postion, direction, track_size);

    cout << "The total seek time is: " << seekTime << endl;

    return 0;
}
