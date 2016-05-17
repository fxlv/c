#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 

int main(void)
{
    int s;
    int port = 200;
    char *hostname;
    char *msg;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    
    s = socket(AF_INET, SOCK_DGRAM, 0);

    hostname = "fx.lv";
    msg = "Hi!";

    server = gethostbyname(hostname);

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
    (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(port);

    sendto(s, msg, strlen(msg), 0, &serveraddr, sizeof(serveraddr));
}
