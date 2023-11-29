#include <iostream>
#include <vector>

using namespace std;

void displayTable(int n, int m, vector<vector<int>> allocation, vector<vector<int>> maximum, vector<vector<int>> need)
{
    cout << "\nProcess ID\tAllocated\tMaximum\t\tNeeded" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << maximum[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(vector<int> available, vector<vector<int>> maximum, vector<vector<int>> allocation, int n, int m)
{
    //int need[100][100];
    vector<vector<int>> need (n, vector<int> (m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    vector<bool> finish(n, false);

    //bool finish[100] = {false};
    //int safeSequence[100];      
    //int work[100];

    vector<int> safeSequence(n);
    vector<int> work(m);

    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i]) 
            {
                bool canAllocate = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (!found)
        {
            return false;
        }
    }

    displayTable(n, m, allocation, maximum, need);
    cout << "\nSafe Sequence: ";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << safeSequence[i];
        if (i != n - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
    return true;
}

int main()
{
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    vector<int> total (m);
    vector<int> available(m, 0);  // int available[100];
    vector<vector<int>> maximum(n, vector<int> (m));// int maximum[100][100];
    vector<vector<int>> allocation(n, vector<int> (m));  // int allocation[100][100];


    cout << "Enter the total number of each resource: ";
    for (int i = 0; i < m; i++)
    {
        cout << "\nEnter the total count of resoure " << i + 1 << endl;
        cin >> total[i];
    }

    cout << "Enter current allocation for each process: \n" << endl;
    for (int i = 0; i < n; i++)
    {     
        cout << "Enter the resources allocated for process " << i+1 << ": ";
        for (int j = 0; j < m; j++)
        {   
            cout << "R" << j+1 << ": ";
            cin >> allocation[i][j];
        }
        cout << "\n";
    }

    for (int i = 0; i < m; i++)
    {   
        for (int j = 0; j < n; j++)
        {
            available[i] += allocation[j][i];
            //available[]
        }
    }

    for (int i = 0; i < m; i++)
    {
        available[i] = total[i] - available[i];
    }


    cout << "Enter maximum demand for each process: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maximum[i][j];
        }
    }


    if (isSafe(available, maximum, allocation, n, m))
    {
        cout << "The system is in a safe state." << endl;
    }
    else
    {
        cout << "The system is in an unsafe state." << endl;
    }


    return 0;
}
