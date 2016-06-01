#include <stdio.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct udphdr *udphdr;
    struct sockaddr_in address;

    char *src_ip = "10.111.102.29";
    char *dst_ip = "10.111.102.21";

    int sport = 2345;
    int dport = 53;

    unsigned char packet[28];
    struct ip *ip;

    int rawsock;

    rawsock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    udphdr = (struct udphdr *)(packet + 20 );

    memset( (char *)udphdr, 0, 8);

    udphdr->uh_sport = htons(sport);
    udphdr->uh_dport = htons(dport);
    udphdr->uh_ulen = htons(8);
    udphdr->uh_sum = 0;

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

    printf("ip->ip_src.s_addr --> %08x\n",ip->ip_src.s_addr);
    printf("ip->ip_dst.s_addr --> %08x\n",ip->ip_dst.s_addr);

    address.sin_family = AF_INET;
    address.sin_port = htons(dport);
    address.sin_addr.s_addr = inet_addr(dst_ip);

    uint16_t csum1;
    /*
    The payload is 0
    Checksum is calculated from 16bit fragments of: 
    src ip, dst ip, proto, udp length and the udp payload.

    UDP length is the part of the payload that starts after IP header
    In this case Ip header is 20 bytes, so UPD paylod starts there and runs for 
    8 bytes and there is no actual payload, just the headers.
    */
    csum1 = net_checksum_tcpudp(8, 17, (unsigned char *)&ip->ip_src, packet+20);
    printf("Checksum: %04x\n", csum1);
    printf("Checksum: %04x (htoned) \n", htons(csum1));
    udphdr->uh_sum = htons(csum1);

    int send_result = sendto( rawsock, &packet, sizeof(packet), 0x0,
        (struct sockaddr *)&address, sizeof(address));
    if(send_result > 0)
        printf("Packet sent (result: %d)\n", send_result);
    else
        printf("Failed to send packet\n");

    return 0;
}
