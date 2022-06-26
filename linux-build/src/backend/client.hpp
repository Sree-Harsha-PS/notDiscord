#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstring>

class Client{
    public:
        Client();
        void Send(char sendMessage[]);
        void Read();

        struct message{
            char sender[32];
            char message[1024]; //Maximum Buffer Length
            char timestamp[32];
        };

        struct message temp;

        std::vector<struct message> messages; //A queue. Add message structs on a separate thread and is acted upon by server

    private:
        int port=8080;
        int bufferlen = 1024;
        int sock = 0, valread;
	    struct sockaddr_in serv_addr;
        int rcvBuffer[1088]; //32+1024+32(MESSAGE STRUCT)
        int sendBuffer[1088];
};

Client::Client(){
    // Create/Initialize a new socket from client
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("\nSocket creation error: ");
        exit(EXIT_FAILURE);
	}

    //Define socket param
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
    printf("\nCONNECTING TO SERVER...");

	// Convert IPv4 and IPv6 addresses from text to binary
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		perror("\nInvalid Address / Address not supported: ");
        exit(EXIT_FAILURE);
	}

    //Connect client socket to server socket
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("\nConnection Failed: ");
        exit(EXIT_FAILURE);
	}

    messages.push_back(temp);

    printf("CONNECTED !");
    printf("\nCLIENT UP AND RUNNING...\n");
}

void Client::Read(){
    if(valread = read(sock, rcvBuffer, sizeof(rcvBuffer))<0){
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

void Client::Send(char sendMessage[]){
    //Deconstruct message struct from queue at messages[0] into from, message, timestamp into sendBuffer
    for(int i=0; i<1024; i++){
        temp.message[i] = sendMessage[i];
    }
    
    for(int i=0; i<1088; i++){
        //printf("e");
        if(i<32)
            sendBuffer[i] = temp.sender[i];
        if(i>=32 && i<1056)
            sendBuffer[i] = temp.message[i-32];
        if(i>=1056 && i<1088)
            sendBuffer[i] = temp.timestamp[i-1056];
    }

    //Dequeue this struct element -no need, need all the messages stored to display

    if((valread = send(sock, sendBuffer, sizeof(sendBuffer), 0))<0){
        perror("\nWhoops, Couldn't SEND");
    }

    for(int i=0; i<1024; i++){sendBuffer[i]=0;}
}