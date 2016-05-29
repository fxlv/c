#include <netinet/ip.h>
#include <netinet/udp.h>
#include <sys/socket.h>
#include <string.h>


#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    struct udphdr *udphdr;
    struct sockaddr_in address;

    char *src_ip = "192.168.1.20";
    char *dst_ip = "192.168.1.108";

    int sport = 2345;
    int dport = 53;

    unsigned char packet[28];
    int raw_socket;
    int on = 1 ;
    struct ip *ip;

    int rawsock;

    rawsock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    udphdr = (struct udphdr *)(packet + 20 );

    memset( (char *)udphdr, 0, 8);

    udphdr->uh_sport = htons(sport);
    udphdr->uh_dport = htons(dport);
    udphdr->uh_ulen = htons(8);
    unsigned short cs = (unsigned short) 0xaf72;
    udphdr->uh_sum = cs;

    ip = (struct ip *)packet;
    memset( (char *)ip, 0, 20 );

    ip->ip_v = 4;
    ip->ip_hl = 5;
    ip->ip_p = IPPROTO_UDP;
    ip->ip_len = 40;
    ip->ip_id = htons(sport);
    ip->ip_ttl = 60;
    ip->ip_sum = 1;
    ip->ip_src.s_addr = inet_addr(src_ip);
    ip->ip_dst.s_addr = inet_addr(dst_ip);

    address.sin_family = AF_INET;
    address.sin_port = htons(dport);
    address.sin_addr.s_addr = inet_addr(dst_ip);

    int send_result = sendto( rawsock, &packet, sizeof(packet), 0x0,
        (struct sockaddr *)&address, sizeof(address));
    if(send_result > 0)
        printf("Packet sent (result: %d)\n", send_result);
    else
        printf("Failed to send packet\n");

    return 0;
}
