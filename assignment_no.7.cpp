#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <unordered_set>
using namespace std;

int fifo(vector<int>& ref_str, int f)
{
    int pg = 0;
    int head = 0;
    vector<int> frame(f, -1);
    for (int i = 0; i < ref_str.size(); i++) // Corrected loop condition
    {
        if (find(frame.begin(), frame.end(), ref_str[i])== frame.end())
        {
            frame[head] = ref_str[i];
            head = (head + 1) % f;
            pg++;
        } 
    }
    return pg;
}
int lrulist(vector<int>& ref_str, int f) {
    list<int> recent;
    unordered_set<int> tank;
    int pgf = 0;

    for (int i = 0; i < ref_str.size(); i++) {
        if (tank.find(ref_str[i]) == tank.end()) {
            pgf++;

            if (tank.size() < f) {
                tank.insert(ref_str[i]);

            } else {
                int pgreplace = recent.front();
                recent.pop_front();
                tank.erase(pgreplace);
                tank.insert(ref_str[i]);
            }
            recent.push_back(ref_str[i]);
        } else {
            recent.erase(find(recent.begin(), recent.end(), ref_str[i]));
            recent.push_back(ref_str[i]);
        }
    }

    return pgf;
}
int optimal(vector <int>& ref_str,int f)
{
    int pgf=0;
    unordered_set <int> tank;


    for(int i=0;i<ref_str.size();i++){

        if(tank.find(ref_str[i])==tank.end()){
            pgf++;
            
            if(tank.size()>=f){
                int far=i;
                bool f=true;

                for(auto tt:tank)
                { 
                    int j=i;
                    for(j;j<ref_str.size();j++){
                        if(tt==ref_str[j])
                        break;
                    }
                    if(j==ref_str.size())
                    {
                        tank.erase(tt);
                        f=false;
                        break;
                    }
                    if(j>far){
                        far=j;
                    }
            }
                if(far<ref_str.size() && f)
                tank.erase(ref_str[far]);

            }
             tank.insert(ref_str[i]);

        }
    }
    return pgf;
}
int main()
{
    int frames, ref_len;
    cout << "Enter the number of frames:" << endl;
    cin >> frames;
    cout << "Enter the number of reference string:" << endl;
    cin >> ref_len;

    if (ref_len <= 0) 
    {
        cout << "Invalid input: Reference string length should be greater than 0" << endl;
        return 1;
    }

    vector <int> ref_str(ref_len);

    cout << "Enter the reference string:" << endl;
    for (auto &ref : ref_str)
        cin >> ref;

     cout << "No Of the Page faults in FIFO  ARE:" << fifo(ref_str, frames) << endl;
     cout << "No Of the Page faults in Lru using list ARE:" << lrulist(ref_str, frames) << endl;
     cout << "No Of the Page faults  using optimall ARE:" << optimal(ref_str, frames) << endl;

    return 0;
}