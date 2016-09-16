#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void sendInitialMessage(int sock){

    //Send some data
    char *message;
    message = "***** HELLO *****\n";
    if( send(sock , message , strlen(message) , 0) < 0)
    {
        puts("Sending initial message failed");
    }

}

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0, serverPort = 0;
    char recvBuff[1024],server_reply[2000];
    char *serverHost;

    struct sockaddr_in serv_addr;
    //printf("%d",argc);
    for (int i = 0; i < argc; ++i) {
        //printf("%d, %s\n",i,argv[i]);
    }

    if (strcmp(argv[1],"-sp") == 0){
        serverPort = atoi(argv[2]);
    }
    else if(strcmp(argv[1],"-sip") == 0){
        serverHost = argv[2];
    }
    if(strcmp(argv[3],"-sp") == 0){
        serverPort = atoi(argv[4]);
    }
    else if(strcmp(argv[3],"-sip") == 0){
        serverHost = argv[4];
    }


    printf("Server port : %d",serverPort);
    printf("Server host : %s",serverHost);
    printf("\n\n");


    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    else{
        puts("Created socket.");
    }
    serv_addr.sin_addr.s_addr = inet_addr("129.10.113.143");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(27993);

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
    else{
        puts("Server Connection Estd.");
    }

    sendInitialMessage(sockfd);
    while(1){

        if( recv(sockfd , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            exit(0);
        }

        server_reply[strlen(server_reply)-1] = 0;
        puts(server_reply);
        char *token = strtok(server_reply, " ");
        int i=0;
        char *host, *op1, *op2, *operand;

        while (token) {
            if(i == 0){
                host = token;
            }
            else if(i == 1){
                op1 = token;
            }
            else if(i == 2){
                operand = token;
            }
            else if(i == 3){
                op2 = token;
            }
            i++;
            token = strtok(NULL, " ");
        }

        if (strcmp(operand,"+") == 0){

        }
    }



    return 0;
}
