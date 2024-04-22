#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int MAX = 500;

void FCFS(vector<int> requests, int head, int max)
{
    int Total_seektime = 0;
    cout << "\nSequence is :";
    for (int i = 0; i < requests.size(); i++)
    {
        Total_seektime = Total_seektime + abs(requests[i] - head);
        cout << requests[i] << " ";
        head = requests[i];
    }

    cout << "\nTotal_seektime is:" << Total_seektime << endl;
}

void SSTF(vector<int> requests, int head, int max)
{
    int Total_seektime = 0;
    cout << "\nSequence is :";
    
    vector<bool> reqdone(requests.size(), false);

    int t = requests.size();
    while (t--)
    {
        int min = MAX;
        int idx = -1;
        for (int i = 0; i < requests.size(); i++)
        {
            if (!reqdone[i] && min > abs(head - requests[i]))
            {
                min = abs(head - requests[i]);
                idx = i;
            }
        }
        reqdone[idx] = true;

        Total_seektime = Total_seektime + abs(requests[idx] - head);
        cout << requests[idx] << " ";
        head = requests[idx];
    }

    cout << "\nTotal_seektime is:" << Total_seektime << endl;
}

void SCAN(vector<int> requests, int head, int max) {
    int totalSeekTime = 0;
    string direction;

    cout << "\nEnter the direction of the scanning (left/right): ";
    cin >> direction;

    sort(requests.begin(), requests.end());

    cout << "\nSequence is: ";

    if (direction == "right") {
        totalSeekTime = abs(max - head) + abs(max - *min_element(requests.begin(), requests.end()));

        auto it = lower_bound(requests.begin(), requests.end(), head);
        for (auto itr = it; itr != requests.end(); ++itr) {
            cout << *itr << " ";
        }

        if (it != requests.begin()) {
            auto itr = --it;
            cout << max << " "; 
            for (itr; itr >= requests.begin(); --itr) {
                cout << *itr << " ";
            }
        }
    }
    else if (direction == "left") {
        totalSeekTime = head + *max_element(requests.begin(), requests.end());

        auto it = upper_bound(requests.begin(), requests.end(), head);
        {
            auto itr = --it;
            for (auto itr = it - 1; itr >= requests.begin(); --itr) {
                cout << *itr << " ";
            }
        }

        it++;

        if (it != requests.end()) {
            cout << "0" << " "; 
            for (auto itr = it; itr != requests.end(); ++itr) {
                cout << *itr << " ";
            }
        }
    }
    else {
        cout << "Invalid direction entered.";
        return;
    }

    cout << "\nTotal seek time: " << totalSeekTime << endl;
}

void CSCAN(vector<int> &requests, int head, int max)
{
    cout << "CSCAN SEQUENCE IS:" << endl;
    int totalSeekTime = 0;
    totalSeekTime = abs(head - max) + max;

    sort(requests.begin(), requests.end());

    auto it = lower_bound(requests.begin(), requests.end(), head);

    if (it != requests.begin())
    {
        totalSeekTime = totalSeekTime + *(--it);
    }

    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] >= head)
            cout << requests[i] << " ";
    }

    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] >= head)
            break;
        cout << requests[i] << " ";
    }

    cout << "\nTotal Seektime  time: " << totalSeekTime << endl;
}
int main()
{
    int head;
    int max;
    int reqs;
    cout << "\nEnter the number of requests:";
    cin >> reqs;

    vector<int> requests(reqs);
    cout << "\nEnter the requests:";
    for (int i = 0; i < reqs; i++)
        cin >> requests[i];

    cout << "\nEnter the intaila head postion:";
    cin >> head;
    cout << "\nEnter the maximum cylinder size:";
    cin >> max;

      FCFS(requests,head,max);
      SSTF(requests,head,max);
      SCAN(requests,head,max);
      CSCAN(requests, head, max);

    return 0;
};