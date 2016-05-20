#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <unistd.h>

void printstderr(char *msg)
{
    fprintf(stderr, msg);
}

void usage()
{
    printstderr("usage: ./udpsender target [ -p port ] [ -c count ] [ -h ]\n");
    printstderr("\t target:\tDestination IP or hostname\n");
    printstderr("\t -p port:\tDestination port where to send the packet\n");
    printstderr("\t -c count:\tHow many packets to send\n");
    printstderr("\t -h:\t\tPrint this usage message\n");
    exit(0);
}

void sender(char *target, int port)
{
    int s;
    char *msg;
    struct sockaddr_in serveraddr;
    struct hostent *server;

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


int main(int argc, char *argv[])
{
    int port = 200;
    char *hostname;

    int opt;
    extern char *optarg;
    char *target = "fx.lv";

    while((opt = getopt(argc, argv, "ht:p:")) != -1){
        switch(opt){
            case 't':
                target = optarg;
                break;
            case 'p':
                port = atoi(optarg); // cast to integer
                break;
            case 'h':
                usage();
                break;
            default:
                usage();
                break;
        }
    }
    // send the packet
    sender(target, port);
}
