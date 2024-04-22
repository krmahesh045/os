#include <iostream>
#include <vector>
#include <algorithm>
#define INT_MIN -100
#define INT_MAX 100


using namespace std;

void print_blocks_processes(vector <int> & blocks,vector <int> &processes)
{
    for (int i = 0; i < blocks.size(); i++)
    cout<<"size of Block-"<<i<<":"<<blocks[i]<<endl;
 
    for (int i = 0; i < processes.size(); i++)
    cout<<"size of Process-"<<i<<":"<<processes[i]<<endl; 
}

void firstfit(vector <int> & blocks,vector <int> &processes)
{
    cout<<"First Fit Allocation"<<endl;
    string msg="Not Allocated";
    
    bool allocated;
    vector <bool> block_allocated(blocks.size(),false);
    for(int i=0;i<processes.size();i++)
    {
        allocated = false;
        for(int j=0;j<blocks.size();j++)
        {
            if(processes[i]<=blocks[j] && !block_allocated[j])
            {
                cout<<"Process "<<i<<" ==> "<<"Block "<<j<<endl;
                allocated=true;
                block_allocated[j] = true;
                break;   
            }
        }
        if(!allocated)
        cout<<"Process "<<i<<" ==> "<<msg<<endl;

    }
}

void nextfit(vector <int> & blocks,vector <int> &processes)
{
    cout<<"Next Fit Allocation"<<endl;
    string msg="Not Allocated";
    bool allocated;
    vector <bool> block_allocated(blocks.size(),false);
    int prev=-1; //

    for(int i=0;i<processes.size();i++)
    {
        int j=(prev+1)%blocks.size();
        allocated = false;
        do
        {
            
            if(processes[i]<=blocks[j] && !block_allocated[j])
            {
                cout<<"Process "<<i<<" ==> "<<"Block "<<j<<endl;
                allocated=true;
                block_allocated[j] = true;
                prev=j;
                break;   
            }
            j= (j+1)%blocks.size();
        } while(j!=prev);
        if(!allocated)
        cout<<"Process "<<i<<" ==> "<<msg<<endl;

    }
}

void bestfit(vector <int> & blocks,vector <int> &processes)
{
    cout<<"Best Fit Allocation"<<endl;
    string msg="Not Allocated";
    
    bool allocated;
    
    int idx;
    vector <bool> block_allocated(blocks.size(),false);
    for(int i=0;i<processes.size();i++)
    {
        int min=INT_MAX;
        allocated = false;
        for(int j=0;j<blocks.size();j++)
        {
            if(processes[i]<=blocks[j] && !block_allocated[j])
            {
                allocated=true;
                if(min>blocks[j])
                {
                    min= blocks[j];
                    idx=j;

                }
               
                 
            }
        }
        if(!allocated)
        cout<<"Process "<<i<<" ==> "<<msg<<endl;
        else
        {
             cout<<"Process "<<i<<" ==> "<<"Block "<<idx<<endl;
             block_allocated[idx] = true;
        }

    }
}

void worstfit(vector <int> & blocks,vector <int> &processes)
{
    cout<<"Worst Fit Allocation"<<endl;
    string msg="Not Allocated";
    
    bool allocated;
    
    int idx;
    vector <bool> block_allocated(blocks.size(),false);
    for(int i=0;i<processes.size();i++)
    {
        int max=INT_MIN;
        allocated = false;
        for(int j=0;j<blocks.size();j++)
        {
            if(processes[i]<=blocks[j] && !block_allocated[j])
            {
                allocated=true;
                if(max<blocks[j])
                {
                    max= blocks[j];
                    idx=j;

                }
               
                 
            }
        }
        if(!allocated)
        cout<<"Process "<<i<<" ==> "<<msg<<endl;
        else
        {
             cout<<"Process "<<i<<" ==> "<<"Block "<<idx<<endl;
             block_allocated[idx] = true;
        }

    }
}


int main()
{
    int b,p;
    cout<<"Enter the number of blocks:"; 
    cin>>b;
    cout<<"\nEnter the number of processes:";
    cin>>p;

    vector < int > blocks(b),processes(p);

    cout<<"\nEnter the size of the blocks:";
    for(auto & block:blocks)
    cin>>block;

    cout<<"\nEnter the size of the processes :";
    for(auto & process:processes)
    cin>>process;
     
    print_blocks_processes(blocks,processes);
    firstfit(blocks,processes);
    nextfit(blocks,processes);
    bestfit(blocks,processes);
    worstfit(blocks,processes);
    

    return 0;
}