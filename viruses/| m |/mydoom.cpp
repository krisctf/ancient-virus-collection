#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MSG_LEN 2048
#define MAX_FILE_LEN 2048
#define BACKLOG 10

char *hostfile = "hosts.txt";

void parse_hosts(char *filename, char **host_list, int *num_hosts) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[MAX_FILE_LEN];
    int i = 0;
    while (fgets(line, MAX_FILE_LEN, fp) != NULL) {
        if (line[0] == '#' || isspace(line[0])) {
            continue;
        }
        char *hostname = strtok(line, " \t\r\n");
        if (hostname == NULL) {
            continue;
        }
        host_list[i] = strdup(hostname);
        i++;
    }
    *num_hosts = i;

    fclose(fp);
}

int main(int argc, char **argv) {
    char *msg = "GET / HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:58.0) Gecko/20100101 Firefox/58.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
    char buf[MAX_MSG_LEN];

    char *host_list[1024];
    int num_hosts = 0;

    parse_hosts(hostfile, host_list, &num_hosts);

    for (int i = 0; i < num_hosts; i++) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        struct hostent *host;
        host = gethostbyname(host_list[i]);
        if (host == NULL) {
            fprintf(stderr, "Unknown host %s\n", host_list[i]);
            close(sockfd);
            continue;
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(80);
        memcpy(&addr.sin_addr, host->h_addr, host->h_length);

        if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
            perror("connect");
            close(sockfd);
            continue;
        }

        snprintf(buf, MAX_MSG_LEN, msg, host_list[i]);
        if (send(sockfd, buf, strlen(buf), 0) == -1) {
            perror("send");
            close(sockfd);
            continue;
        }

        close(sockfd);
    }

    return 0;
}

