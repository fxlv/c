#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <unistd.h>

void usage()
{
    printf("Usage:\n");
    printf("./udpsender -t <target> -p <port>\n\n");
}

int main(int argc, char *argv[])
{
    int s;
    int port = 200;
    char *hostname;
    char *msg;
    struct sockaddr_in serveraddr;
    struct hostent *server;

    int opt;
    extern char *optarg;
    char *target = "fx.lv";

    while((opt = getopt(argc, argv, "t:p:")) != -1){
        switch(opt){
            case 't':
                target = optarg;
                break;
            case 'p':
                port = atoi(optarg); // cast to integer
                break;
            default:
                usage();
        }
    }

    msg = "Hi!"; // default message

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server = gethostbyname(target);

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
    (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(port);
    printf("Sending packet to %s:%d\n", target, port);
    sendto(s, msg, strlen(msg), 0, &serveraddr, sizeof(serveraddr));
}
