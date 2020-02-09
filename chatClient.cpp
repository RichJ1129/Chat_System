//
// Created by Richard Joseph on 2/2/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <zconf.h>
typedef unsigned char BYTE;


int sockfd;
int portNo;
int n;
// Will contain the address of the server to which we connect to
struct sockaddr_in serv_addr;
//Defines a host computer on the Internet
struct hostent *server;
char buffer[500];
char message[500];
char userHandle[11];
bool online = true;

void error(char *msg) {
    perror(msg);
    exit(0);
}


void checkStart(int c, char *v[]){

    if (c < 3) {
        fprintf(stderr, "usage %s hostname port \n", v[0]);
        exit(0);
    }
}


void stringToByte(char* input, BYTE* output) {
    int loop;
    int i;

    loop = 0;
    i = 0;

    while(input[loop] != '\0'){
        output[i++] = input[loop++];
    }

}

void initiate(char *hostName, int portNum) {
    portNo = portNum;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        error("Error no such host");
    }

    server = gethostbyname(hostName);

    if (server == NULL) {
        fprintf(stderr, "Error no such host \n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portNo);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
}

void sendMsg(char *handle) {
    // presents the user's handle and waits for message

    printf("%s: ",userHandle);
    bzero(buffer,500);
    fgets(buffer,499,stdin);

    for (int i = 0; i < 500; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
        }
    }

    // checks if the user typed "\quit"
    if (buffer[0] == '\\' && buffer[1] == 'q' && buffer[2] == 'u' && buffer[3] == 'i' && buffer[4] == 't') {
        online = false;

        // send "\quit" to the server
        n = write(sockfd,buffer,strlen(buffer));

        // check if the write was successful
        if (n < 0) {
            error("ERROR writing to socket");
        }

        // close the connection
        close(sockfd);
    }
    else {
        // clear the message array
        bzero(message,501);

        // put the user handle in it
        strcat(message,handle);

        // put the colon and space init
        strcat(message,": ");

        // put the user's message
        strcat(message,buffer);


        // write the entire message to the server
        n = write(sockfd,message,strlen(message));


        // check if the write was successful
        if (n < 0) {
            error("ERROR writing to socket");
        }
    }
}

void receiveMsg() {
    // clear the message array
    bzero(message,501);

    // read from the server
    n = read(sockfd,message,500);

    // check if the read was successful
    if (n < 0) {
        error("ERROR reading from socket");
    }

    // check if the server sent "\quit"
    if (message[6] == '\\' &&
        message[7] == 'q' &&
        message[8] == 'u' &&
        message[9] == 'i' &&
        message[10] == 't') {

        // if so, end the while loop
        online = 0;

        // close the connection
        close(sockfd);
    }
    else {

        // write the message from the server
        printf("%s\n",message);
    }
}

int main(int argc, char *argv[]) {
    checkStart(argc, argv);

    bzero(userHandle, 10);
    printf("Choose user handle:");
    fgets(userHandle, 10, stdin);


    for(int i = 0; i < 11; i++) {
        if(userHandle[i] == '\n') {
            userHandle[i] = '\0';
        }
    }

    initiate(argv[1], atoi(argv[2]));
    system("clear");
    printf("-Messages-\n");
    while (online == true) {
        sendMsg(userHandle);
        receiveMsg();
    }
    return 0;

}






