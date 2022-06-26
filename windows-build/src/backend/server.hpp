#pragma once

#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<vector>

//RULES - 
//Max name length - 32 bytes
//Max message length - 1024 bytes
//Messages will be sent in the format "from^message^timestamp" string; parsed later into message struct;

class Server{
    public:
        //Initialize Server Socket + Setup options + Define parameters - tcp, port, connections + Bind
        Server();
        void Listen();
        void Accept();
        void Read(int fromSocket);
        void Send(int toSocket);

        struct message{
            char sender[32];
            char message[1024]; //Maximum Buffer Length
            char timestamp[32];
        };

        struct message temp;

        std::vector<struct message> messages; //A queue. Add message structs on a separate thread and is acted upon by server

        int nClient; //Number of clients
        int clients[10]; //Max nClients = 10

    private:
        int port = 8080; //Port on which server resides
        int bufferlen = 1024; //Maximum message length
        int server_fd; //Server instance
        int valread; //If data is read from the client or not
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        int rcvBuffer[1088]; //32+1024+32(MESSAGE STRUCT)
        int sendBuffer[1088];
};

Server::Server(){
    // Initialize/Create a new socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("Socket Init Failed\n");
        exit(EXIT_FAILURE);
    }

    // Set some more options to the created socket
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))){
        perror("Couldn't set socket parameters(setsockopt)\n");
        exit(EXIT_FAILURE);
    }

    // Define address struct parameters(protocol, ,port)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    nClient = 0;

    // Bind the socket to the port
    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Socket Binding Failed\n");
        exit(EXIT_FAILURE);
    }

    messages.push_back(temp);

    printf("\nSERVER IS UP AND RUNNING...");
    printf("\nLISTENING FOR INCOMING CONNECTIONS...\n");
}

//Runs on a separate thread
void Server::Listen(){
    //A maximum of 10 clients handled
    if(!(listen(server_fd, 10) < 0)){
        perror("\nSERVER LISTENING FOR INCOMING CONNECTIONS");
    }
    else{
        perror("\nLISTENING FOR CONNECTIONS");
        exit(EXIT_FAILURE);
    }
}

//Runs on the same thread as Listen() after Listen();
void Server::Accept(){
    if(!((clients[nClient] = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)){
        perror("\nACCEPTED CONNECTION");
        nClient++;
    }
    else{
        perror("\nCONNECTION FAILED");
        exit(EXIT_FAILURE);
    }
}

void Server::Read(int fromSocket){
    if(valread = read(fromSocket, rcvBuffer, sizeof(rcvBuffer))<0){
        perror("\nWhoops, Couldn't READ");
    }
    //Parse metadata and break down the msgdata into from, message, timestamp and put it into msg struct.
    for(int i=0;i<1088;i++){
        if(i<32)
            temp.sender[i] = rcvBuffer[i];
        if(i>=32 && i<1056)
            temp.message[i-32] = rcvBuffer[i];
        if(i>=1056 && i<1088)
            temp.timestamp[i-1056] = rcvBuffer[i]; 
    }
    //Enqueue this message struct
    messages.push_back(temp);

    for(int i=0; i<sizeof(rcvBuffer); i++){rcvBuffer[i]=0;}
}

void Server::Send(int toSocket){
    //Deconstruct message struct from queue at messages[0] into from, message, timestamp into sendBuffer
    for(int i=0; i<1088; i++){
        if(i<32)
            sendBuffer[i] = temp.sender[i];
        if(i>=32 && i<1056)
            sendBuffer[i] = temp.message[i-32];
        if(i>=1056 && i<1088)
            sendBuffer[i] = temp.timestamp[i-1056];
    }
    //Dequeue this struct element
    messages.erase(messages.cbegin()+1);
    
    if((valread = send(toSocket, sendBuffer, sizeof(sendBuffer), 0))<0){
        perror("\nWhoops, Couldn't SEND");
    }

    for(int i=0; i<1024; i++){sendBuffer[i]=0;}
}