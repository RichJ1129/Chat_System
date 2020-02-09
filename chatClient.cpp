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

void sendMsg() {

}

void receiveMsg() {

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
    system("CLS");
    printf("-Messages_");
    while (online == true) {
        if (online == true) {
            sendMsg();
        }
        if (online == true) {
            receiveMsg();
        }
    }
    return 0;

}






