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
char userHandle[10];


void error(char *msg) {
    perror(msg);
    exit(0);
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

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port \n", argv[0]);
        exit(0);
    }

    system("CLS")



    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
        error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}






