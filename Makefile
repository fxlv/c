CFLAGS=-Wall -g
all:
	make memleak
	make segfault
clean:
	rm -rf memleak
	rm -rf segfault
