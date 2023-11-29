#include <iostream>
#include <vector>
using namespace std;

struct PageTable
{
    int frame_no;
    bool valid;
};

bool isPagePresent(vector<PageTable>& PT, int page, int n)
{
    if (PT[page].valid == true)
    {
        return true;
    }
    return false;
}

void updatePageTable(vector<PageTable>& PT, int page, int fr_no, int status)
{
    PT[page].valid = status;
    PT[page].frame_no = fr_no;
}

void printFrameContents(vector<int> frame, int no_of_frames)
{
    for (int i = 0; i < no_of_frames; i++)
        std::cout << frame[i] << '\t';
    std::cout << "\t"
              << "M";
    std::cout << std::endl;
}
void printFrameContentsH(vector<int> frame, int no_of_frames)
{
    for (int i = 0; i < no_of_frames; i++)
        std::cout << frame[i] << '\t';
    std::cout << "\t"
              << "H";
    std::cout << std::endl;
}

int main()
{
    int n, no_of_frames, page_fault = 0, page_hits = 0, current = 0;
    bool flag = false;

    std::cout << "\nEnter the no. of pages:\n";
    std::cin >> n;

    vector<int> reference_string(n); //int reference_string[n];

    std::cout << "\nEnter the reference string (different page numbers):\n";
    for (int i = 0; i < n; i++)
    {
        std::cin >> reference_string[i];
    }

    std::cout << "\nEnter the no. of frames you want to give to the process:";
    std::cin >> no_of_frames;

    vector<int> frame(no_of_frames);  //int frame[no_of_frames];
    for (int i = 0; i < no_of_frames; i++)
    {
        frame[i] = -1;
    }

    vector<PageTable> PT(50);   //PageTable PT[50];

    for (int i = 0; i < 50; i++)
    {
        PT[i].valid = false;
    }

    std::cout << "\n  The Contents inside the Frame array at different time:  \n\n";
    for (int i = 0; i < no_of_frames; i++)
    {
        std::cout << "F" << i << "\t";
    }
    std::cout << "Hit(H) or Miss(M)";
    std::cout << "\n\n";

    for (int i = 0; i < n; i++)
    {
        if (!(isPagePresent(PT, reference_string[i], n)))
        {
            page_fault++;

            if (flag == false && current < no_of_frames)
            {
                frame[current] = reference_string[i];
                printFrameContents(frame, no_of_frames);
                updatePageTable(PT, reference_string[i], current, true);
                current = current + 1;
                if (current == no_of_frames)
                {
                    current = 0;
                    flag = true;
                }
            }
            else
            {
                updatePageTable(PT, frame[current], -1, false);
                frame[current] = reference_string[i];
                printFrameContents(frame, no_of_frames);
                updatePageTable(PT, reference_string[i], current, true);
                current = (current + 1) % no_of_frames;
            }
        }
        else
        {
            printFrameContentsH(frame, no_of_frames);
            page_hits++;
        }
    }

    std::cout << "\nTotal No. of Page Faults = " << page_fault << std::endl;
    std::cout << "Total No. of Page Hits = " << page_hits << std::endl;
    std::cout << "\nPage Fault ratio = " << static_cast<float>(page_fault) / n << std::endl;
    std::cout << "Page Hit Ratio = " << static_cast<float>(page_hits) / n << std::endl;

    return 0;
}
