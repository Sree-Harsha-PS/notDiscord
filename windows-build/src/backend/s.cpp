#include<iostream>
#include "server.hpp"

int main(){
    Server myserver;
    int iomode=0;
    myserver.Listen();
    myserver.Accept();
    while(1){
        if(!iomode){ //receive
            for(int i=0; i<myserver.nClient; i++)
                myserver.Read(myserver.clients[i]);
            puts(myserver.messages[1].message);
            iomode=1;
            printf("%d", myserver.nClient);
        }
        if(iomode){ //send
            for(int i=0; i<myserver.nClient; i++){
                myserver.Send(myserver.clients[i]);
            }
            iomode=0;
        }
    }
    return 0;
}