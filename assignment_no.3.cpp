#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(){
    int ptocpipe[2],ctoppipe[2];
    int returnstatus1,returnstatus2;
    
    char parentmsg[100];
    char childmsg[100];
    char receivedmsg[100];
    
    returnstatus1=pipe(ptocpipe);
    if(returnstatus1==-1){
        cout<<"error"<<endl;
    }
    
    returnstatus2=pipe(ctoppipe);
    if(returnstatus2==-1){
        cout<<"error"<<endl;
    }
    
    int pid=fork();
    if(pid==-1){
        cout<<"fork failed"<<endl;
    }
    
    else if(pid==0){
        while(true){
            close(ptocpipe[1]);
            close(ctoppipe[0]);
            
            read(ptocpipe[0],receivedmsg,sizeof(receivedmsg));
            cout<<"child (PID"<<getpid<<"):received from parent:"<<receivedmsg<<endl;
            
            if(strcmp(receivedmsg,"stop")==0){
                cout<<"chat terminated"<< endl;
                break;
            }
            
            cout<<"child (PID"<<getpid<<"):enter message for parent:"<<endl;
            cin.getline(childmsg,sizeof(childmsg));
            write(ctoppipe[1],childmsg,strlen(childmsg)+1);
            
        }
    }
    else{
        while(true){
            close(ptocpipe[0]);
            close(ctoppipe[1]);
            
            cout<<"parent (PID"<<getpid<<"):enter message for child:"<<endl;
            cin.getline(parentmsg,sizeof(parentmsg));
            write(ptocpipe[1],parentmsg,strlen(parentmsg)+1);
            
             
            if(strcmp(parentmsg,"stop")==0){
                cout<<"chat terminated"<< endl;
                break;
            }
            
            
            read(ctoppipe[0],receivedmsg,sizeof(receivedmsg));
            cout<<"parent (PID"<<getpid<<"):received from child:"<<receivedmsg<<endl;
            
            
        }
    }
    
    
    
    
    
    
    
    
    return 0;
}