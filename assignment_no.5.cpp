#include <iostream>
#include <vector>

using namespace std;

class bankers_algo
{
private:
 int num_processes;
 int num_resources;
 vector< vector<int> > allocation;
 vector< vector<int> > max;
 vector<int> available;
 vector< vector<int> > need;
 vector<int> sequence;

public:
bankers_algo() {};
 
void get_data(){
    cout <<"Enter the number of processes: ";
    cin>>num_processes;
    cout <<"Enter the number of resources: ";
    cin>>num_resources;

    allocation.resize(num_processes,vector<int>(num_resources,0));
    max.resize(num_processes,vector<int>(num_resources,0));
    need.resize(num_processes,vector<int>(num_resources,0));

    cout <<"Enter the allocation matrix: ";

    for(int i=0;i<num_processes;i++){
        for(int j=0;j<num_resources;j++){
            cin>>allocation[i][j];
        }
    }

    cout <<"Enter the max matrix: ";

    for(int i=0;i<num_processes;i++){
        for(int j=0;j<num_resources;j++){
            cin>>max[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    cout <<"Enter the available: ";
    available.resize(num_resources);
    for(int i=0;i<num_resources;i++){
        cin>>available[i];
    }
}

bool isSafe(vector<int> &work,vector<bool> &finish){
int count = 0;
while(count<num_processes){
    bool found = false;
   for(int i=0;i<num_processes;i++){
         if(!finish[i]){
                bool canBeAllocated = true;
                for(int j=0;j<num_resources;j++){
                    if(need[i][j]>work[j]){
                        canBeAllocated = false;
                        break;
                    }
                }
         
         if(canBeAllocated){
             for(int j=0;j<num_resources;j++){
                 work[j] += allocation[i][j];
             }
             finish[i] = true;
             sequence.push_back(i);
             found = true;
             count++;
         }
   }
   }
    if(!found){
         return false;
    }
}
return true;
}

void execute_algo(){
    vector<int> work = available;
    vector<bool> finish(num_processes,false);
    if(isSafe(work,finish)){
        cout <<"The system is in safe state\n";
        cout <<"The safe sequence is: ";
        for(int i=0;i<num_processes;i++){
            cout <<"p"<<sequence[i]<<" ";
        }
    }
    else{
        cout <<"The system is in unsafe state\n";
    }


}



};

int main()
{
    bankers_algo b;
    b.get_data();
    b.execute_algo();
    return 0;
}