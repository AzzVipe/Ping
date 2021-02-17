#include <ping.h>

void send_ipv4(void )
{
	int len;
	struct icmp *icmp;

	icmp = (struct icmp *) sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = htons(pid);
	icmp->icmp_seq = htons(nsent++);
	
	memset(icmp->icmp_data, 0xa5, datalen);
	if (gettimeofday((struct timeval *)icmp->icmp_data, NULL) != 0) 
		fprintf(stderr, "gettimeofday error : \n");
	
	printf("Sequence : %d   send_ipv4 Time : %ld\n", icmp->icmp_seq, ((struct timeval *)icmp->icmp_data)->tv_sec);
	len = 8 + datalen;
	icmp->icmp_cksum = 0;

	icmp->icmp_cksum = calc_checksum((uint16_t *) icmp, len);
	// printf("after send_ipv4 Time : %ld\n", ((struct timeval *)icmp->icmp_data)->tv_sec);


	fprintf(stderr, "send_ipv4: Sending ping packet seq=#%d id=%d\n\n", nsent - 1, pid);
	sendto(sockfd, sendbuf, len, 0, addri->ai_addr, addri->ai_addrlen);
}


uint16_t calc_checksum(uint16_t *data, int len)
{
	uint32_t sum = 0;
	uint16_t *w = data;

	int nleft = len;
	uint16_t answer = 0;

	while(nleft > 1) {
		sum += htons(*w++);
		nleft -= 2;
	}

	if (nleft == 1) {
		*(unsigned char *) (&answer) = htons(*(unsigned char *) w);
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = htons(~sum);

	return answer;

}
