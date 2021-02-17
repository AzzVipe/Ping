CC=cc
OBJSPATH=~/Dropbox/advanced_coding/clibs/objs
HEADSPATH=~/Dropbox/advanced_coding/clibs/headers
HEADER=./
OBJS=readloop.o proc_ipv4.o send_ipv4.o tvsub.o send_ipv6.o proc_ipv6.o
CFLAGS=-I. -I $(HEADSPATH)

ping: $(OBJS) ping.c
	$(CC) -g -o ping ping.c $(CFLAGS) $(OBJS)

readloop: 
	$(CC) -c -g -o readloop.o readloop.c $(CFLAGS)

proc_ipv4:
	$(CC) -c -g -o proc_ipv4.o proc_ipv4.c $(CFLAGS) 

send_ipv4:
	$(CC) -c -g -o send_ipv4.o send_ipv4.c $(CFLAGS) 

tvsub:
	$(CC) -c -g -o tvsub.o tvsub.c $(CFLAGS) 

proc_ipv6:
	$(CC) -c -g -o proc_ipv6.o proc_ipv6.c $(CFLAGS) 

send_ipv6:
	$(CC) -c -g -o send_ipv6.o send_ipv6.c $(CFLAGS) 


