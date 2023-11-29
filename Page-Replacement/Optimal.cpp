#include <iostream>
#include <vector>

using namespace std;

bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

int predict(vector<int> pg, vector<int> &fr, int pn, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn) //here we traversed the entire reference string, which must mean that the position i is empty or -1
            return i;
    }
    return (res == -1) ? 0 : res;
}

void printFrames(vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
    {
        if (fr[i] == -1)
            cout << "- ";
        else
            cout << fr[i] << " ";
    }
}

void optimalPage(vector<int> pg, int pn, int fn)
{
    vector<int> fr(fn, -1); // Initialize frames with -1
    int hit = 0;
    char result;

    cout << "Page String\tFrames\t\tHit/Miss\n";

    for (int i = 0; i < pn; i++)
    {
        cout << pg[i] << "\t\t";

        if (search(pg[i], fr))
        {
            hit++;
            result = 'H';
        }
        else
        {
            if (fr[fr.size() - 1] == -1)
            {
                fr[fr.size() - 1] = pg[i];
                result = 'M';
            }
            else
            {
                int j = predict(pg, fr, pn, i + 1);
                result = 'M';
                fr[j] = pg[i];
            }
        }

        printFrames(fr);
        cout << "\t\t" << result << endl;
    }

    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

int main()
{
    int pn, fn;

    cout << "Enter the number of page references: ";
    cin >> pn;

    vector<int> pg(pn);  //int pg[pn];

    cout << "Enter the page reference string: ";
    for (int i = 0; i < pn; i++)
    {
        cin >> pg[i];
    }

    cout << "Enter the number of frames: ";
    cin >> fn;

    optimalPage(pg, pn, fn);

    return 0;
}
