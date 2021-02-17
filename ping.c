#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <ping.h>

int datalen = 56;
int nsent = 1;
pid_t pid;
struct addrinfo *addri;
int sockfd;
char sendbuf[MAXLINE];

struct ping_t *ping_ptr;
struct ping_t ping_ipv4 = {proc_ipv4, send_ipv4, IPPROTO_ICMP};
struct ping_t ping_ipv6 = {proc_ipv6, send_ipv6, IPPROTO_ICMPV6};

int main(int argc, char *argv[])
{
	int rv;
	char *host;
	
	if (argc != 2) {
		fprintf(stderr, "Usage : %s <hostname>\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	pid = getpid() & 0xffff;	/* ICMP ID field is 16 bits */

	if ((addri = Host_serv(argv[1], NULL)) == NULL)
		exit(EXIT_FAILURE);

	if ((host = Socket_ntop(addri->ai_addr)) == NULL)
		exit(EXIT_FAILURE);

	printf("PING %s (%s) %d bytes of data.\n", addri->ai_canonname? addri->ai_canonname : host, host, datalen);

	signal(SIGALRM, sig_alarm);

	if (addri->ai_family == AF_INET) {
		fprintf(stderr, "IPV4\n");
		ping_ptr = &ping_ipv4;
	}
	else if (addri->ai_family == AF_INET6) {
		fprintf(stderr, "IPV6\n");
		ping_ptr = &ping_ipv6;
	}

	readloop(addri);
	

	return 0;
}

struct addrinfo *Host_serv(char *hostname, char* service)
{
	int rv;
	struct addrinfo *addr, hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family    = AF_UNSPEC;
	hints.ai_flags     = AI_CANONNAME;
	hints.ai_socktype  = SOCK_RAW;

	if ((rv =getaddrinfo(hostname, service, &hints, &addr)) != 0) {
		printf("getaddrinfo error : %s\n", gai_strerror(rv));
		return NULL;
	}

	return addr;
}



void sig_alarm(int signum)
{
	ping_ptr->fsend();
	alarm(1);

	return;
}

char *Socket_ntop(struct sockaddr *addr)
{
	char *buf = malloc(sizeof(char) * BUFSIZ);
	struct sockaddr_in *sockaddr = (struct sockaddr_in *) addr;

	if (inet_ntop(sockaddr->sin_family, &sockaddr->sin_addr, buf, BUFSIZ) == NULL) {
		free(buf);

		return NULL;
	}

	return buf;
}
