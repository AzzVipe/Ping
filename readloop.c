#include <ping.h>

void readloop(struct addrinfo *ai)
{
	int nbytes;
	char buf[1024], recvbuf[1024];
	struct msghdr msghdr;
	struct iovec iov;
	struct timeval tv;

	fprintf(stderr, "readloop: creating raw socket...\n");
	
	if ((sockfd = socket(ai->ai_family, SOCK_RAW, ping_ptr->proto)) < 0) {
		perror("socket error");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "readloop: raw socket created\n");

	setuid(getuid());

	sig_alarm(SIGALRM);

	iov.iov_base = buf;
	iov.iov_len = sizeof(buf);

	msghdr.msg_name = ai->ai_addr;
	msghdr.msg_iov = &iov;
	msghdr.msg_iovlen = 1;

	msghdr.msg_control = recvbuf;

	fprintf(stderr, "\nWaiting for ping reply...\n\n");
	
	for (; ;) {
		msghdr.msg_controllen = sizeof(recvbuf);
		msghdr.msg_namelen = ai->ai_addrlen;

		nbytes = recvmsg(sockfd, &msghdr, 0);
		if (nbytes == -1) {
			if (errno == EINTR)
				continue;
			perror("recvmsg error");
			return;
		}
		fprintf(stderr, "readloop: Ping reply received.\n");
		gettimeofday(&tv, NULL);
		ping_ptr->fproc(buf, nbytes, &msghdr, &tv);
	}
}
