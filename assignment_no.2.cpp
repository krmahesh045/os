#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct process
{
    int pid, at, bt, ct, tat, wt, st, rt ;
};

bool Atcomp(const process a, const process b)
{
    if (a.at != b.at)
        return a.at < b.at;
    if (a.bt != b.bt)
        return a.bt < b.bt;
    return a.pid < b.pid;
}

bool Btcomp(const process a, const process b)
{
    if (a.bt != b.bt)
        return a.bt < b.bt;
    if (a.at != b.at)
        return a.at < b.at;
    return a.pid < b.pid;
}

void FCFS(vector<process> ps, int p)
{
    cout << "\nFCFS" << endl;
    int currenttime = 0;
    cout << "\npid\tat \tbt \tst \tct \ttat\twt \trt ";
    for (int i = 0; i < p; i++)
    {
        ps[i].st = max(ps[i].at, currenttime);
        if (currenttime < ps[i].at)
            currenttime = ps[i].at;
        ps[i].ct = currenttime + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].st - ps[i].at;
        currenttime = ps[i].ct;
        cout << "\n"
             << ps[i].pid << "\t" << ps[i].at << "\t" << ps[i].bt << "\t" << ps[i].st << "\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << "\t";
    }
}

void SJF(vector<process> ps, int p)
{
    cout << "\nSJF" << endl;
    int currenttime = 0;
    cout << "\npid\tat \tbt \tst \tct \ttat\twt \trt ";
    for (int i = 0; i < p;)
    {
        ps[i].st = max(ps[i].at, currenttime);
        if (currenttime < ps[i].at)
            currenttime = ps[i].at;
        ps[i].ct = currenttime + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].st - ps[i].at;
        currenttime = ps[i].ct;
        cout << "\n"
             << ps[i].pid << "\t" << ps[i].at << "\t" << ps[i].bt << "\t" << ps[i].st << "\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << "\t";
        i++;
        int j = i;
        if (j + 1 != p)
        {
            for (j; j < p; j++)
            {
                if (ps[j].at > currenttime)
                    break;
            }
            sort(ps.begin() + i, ps.begin() + j, Btcomp);
        }
    }
}
int main()
{
    int p;
    cout << "\nEnter the no of processes:";
    cin >> p;

    vector<process> ps(p);
    for (int i = 0; i < p; i++)
    {
        ps[i].pid = i;
        cout << "\nEnter details of process  " << i << " (at,bt):";
        cin >> ps[i].at >> ps[i].bt;
    }
    sort(ps.begin(), ps.end(), Atcomp);
    FCFS(ps, p);
    SJF(ps, p);
    return 0;
}