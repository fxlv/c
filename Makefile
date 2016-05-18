CFLAGS=-Wall -g
all:
	make memleak
	make segfault
	make udpsender
	make args
clean:
	rm -rf memleak
	rm -rf segfault
	rm -rf udpsender
	rm -rf args
lint:
	splint *.c
