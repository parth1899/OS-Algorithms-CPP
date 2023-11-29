#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <vector>

void displayCacheHeader()
{
    std::cout << "Cache\tHit/Miss\n";
}

void displayCache(std::unordered_set<int> &s, int page, bool isHit, bool displayHeader)
{
    if (displayHeader)
    {
        displayCacheHeader();
    }

    for (int p : s)
    {
        std::cout << p << "\t";
        if (p == page && isHit)
        {
            std::cout << "Hit";
        }
        else
        {
            std::cout << "Miss";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int pageFaults(std::vector<int> pages, int n, int capacity)
{
    std::unordered_set<int> s;
    std::unordered_map<int, int> indexes;
    int page_faults = 0;

    bool displayHeader = true;

    for (int i = 0; i < n; i++)
    {
        std::cout << "Page " << pages[i] << " - \n";

        bool isHit = (s.find(pages[i]) != s.end());

        if (!isHit)
        {
            if (s.size() == capacity)
            {
                int lru = INT_MAX, val;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                    }
                }
                s.erase(val);
            }
            s.insert(pages[i]);
            page_faults++;
        }
        displayCache(s, pages[i], isHit, displayHeader);
        displayHeader = false;
        indexes[pages[i]] = i;
    }

    return page_faults;
}

int main()
{
    int n;

    std::cout << "Enter the number of pages: ";
    std::cin >> n;

    std::vector<int> pages(n);
    //int pages[n];

    std::cout << "Enter the page references:" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin >> pages[i];
    }

    int capacity;
    std::cout << "Enter the capacity of the cache: ";
    std::cin >> capacity;

    std::cout << "Page Faults: " << pageFaults(pages, n, capacity) << std::endl;

    return 0;
}
