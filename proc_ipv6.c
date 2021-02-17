#include <ping.h>

void proc_ipv6(char *buf, size_t len, struct msghdr *msghdr, struct timeval *tvrecv)
{
	size_t ip_len, icmp6_len;

	double rtt;
	struct icmp6_hdr *icmp;
	struct timeval *tvsend, elapsed;
	char *canonname;

	icmp = (struct icmp6_hdr *) buf;

	canonname = addri->ai_canonname? addri->ai_canonname : "???";

	if ((icmp6_len = len - datalen) < 8) {
		puts("1");
		return;					/* malformed packet */
	}

	if (icmp->icmp6_type != ICMP6_ECHO_REPLY) {
		printf("Icmp type : %d\nEcho reply value : %d\n", icmp->icmp6_type, ICMP6_ECHO_REPLY);
		return;
	}

	if ((len - icmp6_len) < 16) {
		puts("3");
		return;
	}

	if (ntohs(icmp->icmp6_id) != pid) {
		puts("4");
		return;
	}

	tvsend = (struct timeval *) (icmp + 1);
	tvsub(tvrecv, tvsend, &elapsed);

	rtt = elapsed.tv_sec * 1000.0 + elapsed.tv_usec / 1000.0;
	printf("Time : %ld\n", tvsend->tv_sec);
	printf("%ld bytes recieved from %s (%s) : seq = %d time = %.3fms \n", icmp6_len, canonname, Socket_ntop(msghdr->msg_name), icmp->icmp6_seq, rtt);

}

