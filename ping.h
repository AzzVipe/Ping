#ifndef __PING_H_
#define __PING_H_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
	
#define MAXLINE 1024

struct ping_t {
	void (*fproc)(char *, size_t, struct msghdr *, struct timeval *);
	void (*fsend)(void);

	int proto;
};

extern int sockfd;
extern int nsent;
extern pid_t pid;
extern struct addrinfo *addri;
extern int datalen;
extern char sendbuf[MAXLINE];
extern struct ping_t *ping_ptr;

void sig_alarm(int signum);
struct addrinfo *Host_serv(char *hostname, char* service);
char *Socket_ntop(struct sockaddr *addr);
void readloop(struct addrinfo *ai);
void proc_ipv4(char *buf, size_t len, struct msghdr *msghdr, struct timeval *tvrcev);
void send_ipv4(void);
uint16_t calc_checksum(uint16_t *data, int len);
void tvsub(struct timeval *tvrecv, struct timeval *tvsend, struct timeval *elapsed);

void proc_ipv6(char *buf, size_t len, struct msghdr *msghdr, struct timeval *tvrcev);
void send_ipv6(void);



#endif
