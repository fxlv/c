CFLAGS=-Wall -g
all:
	make memleak
	make segfault
	make udpsender
clean:
	rm -rf memleak
	rm -rf segfault
	rm -rf udpsender
lint:
	splint *.c
