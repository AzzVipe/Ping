#include <ping.h>

void send_ipv6(void )
{
	int len;
	struct icmp6_hdr *icmp;

	icmp = (struct icmp6_hdr *) sendbuf;
	icmp->icmp6_type = ICMP6_ECHO_REQUEST;
	icmp->icmp6_code = 0;
	icmp->icmp6_id = htons(pid);
	icmp->icmp6_seq = htons(nsent++);
	
	fprintf(stderr, "ID : %d\n", icmp->icmp6_id );
	memset(icmp + 1, 0xa5, datalen);
	if (gettimeofday((struct timeval *)(icmp + 1), NULL) != 0) 
		fprintf(stderr, "gettimeofday error : \n");
	
	len = 8 + datalen;

	fprintf(stderr, "send_ipv6: Sending ping packet seq=#%d id=%d\n", nsent - 1, pid);
	if (sendto(sockfd, sendbuf, len, 0, addri->ai_addr, addri->ai_addrlen) == -1)
		perror("sendto error");
}
