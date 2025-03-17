#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_HOPS 30
#define TIMEOUT 2
#define UDP_PORT 33434

void traceroute_udp(char *destination) {
    struct sockaddr_in dest_addr;
    int udp_sock, icmp_sock, ttl, bytes_sent, bytes_received;
    char recv_buffer[512];
    struct timeval start, end;
    
    udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    icmp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (udp_sock < 0 || icmp_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, destination, &dest_addr.sin_addr);
    dest_addr.sin_port = htons(UDP_PORT);

    printf("Tracing route to %s:\n", destination);

    for (ttl = 1; ttl <= MAX_HOPS; ttl++) {
        setsockopt(udp_sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));

        gettimeofday(&start, NULL);
        bytes_sent = sendto(udp_sock, "X", 1, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
        if (bytes_sent <= 0) {
            perror("sendto failed");
            continue;
        }

        struct sockaddr_in reply_addr;
        socklen_t addr_len = sizeof(reply_addr);

        bytes_received = recvfrom(icmp_sock, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr*)&reply_addr, &addr_len);
        gettimeofday(&end, NULL);

        if (bytes_received > 0) {
            double rtt = ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_usec - start.tv_usec) / 1000.0);
            printf("%2d  %s  %.2f ms\n", ttl, inet_ntoa(reply_addr.sin_addr), rtt);
            if (reply_addr.sin_addr.s_addr == dest_addr.sin_addr.s_addr) {
                break; // Destination reached
            }
        } else {
            printf("%2d  *\n", ttl);
        }
    }
    close(udp_sock);
    close(icmp_sock);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <destination>\n", argv[0]);
        return 1;
    }
    traceroute_udp(argv[1]);
    return 0;
}
