#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <zconf.h>


int sockfd;
int portNum;
int n;
// Will contain the address of the server to which we connect to
struct sockaddr_in serv_addr;
//Defines a host computer on the Internet
struct hostent *server;
char buffer[501];
char message[489];
char userHandle[11];
bool online = true;


/* Function
 * Checks to see if the program has the correct amount of
arguments when entered in the console. If it does not
it will quit out of the program.*/


void checkStart(int c, char *v[]){
    if (c < 3) {
        fprintf(stderr, "usage %s hostname port \n", v[0]);
        exit(0);
    }
}


/* Function
 * Prints error message that is passed to it. Obtained
 * from linux source in readme file.*/


void error(char *msg) {
    perror(msg);
    exit(0);
}


/* Function
 * Modularized version of code in linux source. Initiates connection
 * to the server specified in your terminal command.
 * */


void initiate(char *hostName, int port) {
    portNum = port;
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
    serv_addr.sin_port = htons(portNum);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
}


/* Function
 * Function to allow the program to send bytes to
 * the socket.*/


void sendMsg(char *handle) {
    printf("%s: ",userHandle);
    bzero(buffer, sizeof(buffer));
    fgets(buffer,488,stdin);

    //Range based loop the removes null terminator from the userHandle
    for(char & i : buffer) {
        if (i == '\n') {
            i = '\0';
        }
    }

    //If statement seeing if first 5 values in the array are the /quit statement
    if (buffer[0] == '/' && buffer[1] == 'q' && buffer[2] == 'u' && buffer[3] == 'i' && buffer[4] == 't') {
        online = false;

        n = write(sockfd,buffer,strlen(buffer));

        if (n < 0) {
            error("ERROR writing to socket");
        }
        close(sockfd);
        exit(0);
    }

    else {
        bzero(message, sizeof(message));
        strcat(message, handle);
        strcat(message,": ");
        strcat(message, buffer);
        n = write(sockfd,message,strlen(message));
        if (n < 0) {
            error("ERROR writing to socket");
        }
    }
}


/* Function
 * Function to allow the program to read bytes from
 * the socket.*/


void receiveMsg() {
    // clears the message array
    bzero(message, sizeof(message));

    // read message from the server
    n = read(sockfd,message,500);

    // checks to see if the read was successful
    if (n < 0) {
        error("ERROR reading from socket");
    }
    //For loop that checks to see if /quit was received. If it has program is ended.
    for(int i = 0; i < sizeof(message); i++) {
        if (message[i] == '/' && message[i+1] == 'q' && message[i+2] == 'u' && message[i+3] == 'i' && message[i+4] == 't') {
            online = false;
            close(sockfd);
            printf("The Chat server has closed goodbye.");

            exit(0);
        }
    }


    printf("%s\n",message);
}


int main(int argc, char *argv[]) {
    checkStart(argc, argv);

    bzero(userHandle, sizeof(userHandle));
    printf("What would you like your username to be (Limit 10 Characters)?");
    fgets(userHandle, 10, stdin);


    for(int i = 0; i < 11; i++) {
        if(userHandle[i] == '\n') {
            userHandle[i] = '\0';
        }
    }

    initiate(argv[1], atoi(argv[2]));
    system("clear");
    printf("Messages\n");
    while (online == true) {
        sendMsg(userHandle);
        receiveMsg();
    }
    return 0;
}






