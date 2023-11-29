#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cscan(vector<int> requests, int initial_Position, string direction, int track_size)
{
    int total_seek_time = 0;
    vector<int> left, right;
    int flag1 = 0, flag2 = 0; //to know if to add track_size-1 or not  
    int currentPosition = initial_Position;

    left.push_back(0);
    right.push_back(track_size - 1);

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

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int run = 2;
    while (run--)
    {
        if (direction == "right")
        {
            for (int i = 0; i < right.size(); i++)
            {
                int distance = abs(right[i] - currentPosition);
                total_seek_time += distance;
                currentPosition = right[i];
            }
            direction = "left";
            flag1 = 1;
            currentPosition = 0;
            //total_seek_time += track_size - 1;
        }

        else if (direction == "left")
        {
            for (int i = 0; i < left.size(); i++)
            {
                int distance = abs(left[i] - currentPosition);
                total_seek_time += distance;
                currentPosition = left[i];
            }
            direction = "right";
            currentPosition = track_size - 1;
            flag2 = 1;
            //total_seek_time += track_size - 1;
        }
    }

    if (flag1 == 1 && flag2 == 1)
    {
        total_seek_time += track_size - 1;
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

    int seekTime = cscan(requests, initial_Postion, direction, track_size);

    cout << "The total seek time is: " << seekTime << endl;

    return 0;
}
