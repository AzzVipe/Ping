#include <ping.h>

void tvsub(struct timeval *tvrecv, struct timeval *tvsend, struct timeval *elapsed)
{
	elapsed->tv_usec = tvrecv->tv_usec - tvsend->tv_usec;
	elapsed->tv_sec  = tvrecv->tv_sec - tvsend->tv_sec;

	if (elapsed->tv_usec < 0) {
		elapsed->tv_sec = tvrecv->tv_sec - 1;
		elapsed->tv_usec = elapsed->tv_usec + 1000000;
	}
}