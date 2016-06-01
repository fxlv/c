CFLAGS=-Wall -g
all:
	make memleak
	make segfault
	make udpsender
	make args
	make memset
	gcc net-checksum.c udpraw.c -o udpraw
clean:
	rm -rf memleak
	rm -rf segfault
	rm -rf udpsender
	rm -rf args
	rm -rf memset
	rm -rf udpraw
lint:
	splint *.c
