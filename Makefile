CFLAGS=-Wall -g
all:
	make memleak
	make segfault
	make args
	make memset
clean:
	rm -rf memleak
	rm -rf segfault
	rm -rf args
	rm -rf memset
lint:
	splint *.c
