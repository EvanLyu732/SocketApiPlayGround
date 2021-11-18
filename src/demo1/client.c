#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


int main(int argc, char **argv)
{
    int MAXLINE = 5000;
    int sockfd, n;
    char recbuf[MAXLINE + 1];
    struct sockaddr_in serveraddr;
    

    if (argc != 2) {
        printf("incorrect arguments");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        printf("socket error");
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(13);

    if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0) {
        printf("inet_pton error for %s", argv[1]);
    }

    if (connect(sockfd, &serveraddr, sizeof(serveraddr)) < 0)  {
        printf("connect error");
    }

    while ( (n = read(sockfd, recbuf, MAXLINE)) > 0) {
        recbuf[n] = 0;
    }

    if (n < 0)
        printf("read error");

    exit(0);
}