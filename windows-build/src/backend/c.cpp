#include <iostream>
#include "client.hpp"

int main(){
    Client myclient;
    int iomode=0;
    int run=1;
    char inputMsg[1024];
    while(run){
        if(!iomode){
            fgets(inputMsg, 1024, stdin);
            myclient.Send(inputMsg);
            iomode=1;
        }
        if(iomode){
            myclient.Read();
            fputs(myclient.messages[0].message, stdin);
            iomode=0;
        }
    }
    return 0;
}