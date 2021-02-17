#include <ping.h>

void proc_ipv4(char *buf, size_t len, struct msghdr *msghdr, struct timeval *tvrecv)
{
	size_t ip_len, icmp_len;

	double rtt;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend, elapsed;
	char *canonname;

	ip = (struct ip *) buf;
	ip_len = ip->ip_hl << 2;	/* length of IP header */
	if (ip->ip_p != IPPROTO_ICMP)
		return;					/* not ICMP */

	canonname = addri->ai_canonname? addri->ai_canonname : "???";

	icmp = (struct icmp *) (buf + ip_len);

	if ((icmp_len = len - ip_len) < 8)
		return;					/* malformed packet */

	if (icmp->icmp_type != ICMP_ECHOREPLY) {
		if (icmp_len < 16)
			return;

		if (icmp->icmp_id != pid)
			return;

	}
	tvsend = (struct timeval *) icmp->icmp_data;
	tvsub(tvrecv, tvsend, &elapsed);

	printf("Sequence : %d   send_ipv4 Time : %ld\n", icmp->icmp_seq, ((struct timeval *)icmp->icmp_data)->tv_sec);

	rtt = elapsed.tv_sec * 1000.0 + elapsed.tv_usec / 1000.0;
	printf("%ld bytes recieved from %s (%s) : seq = %d time = %.3fms \n\n", icmp_len, canonname, Socket_ntop(msghdr->msg_name), ntohs(icmp->icmp_seq), rtt);

}

