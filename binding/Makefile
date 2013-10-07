CC=gcc
CFLAGS=-I/usr/include/lua5.2/ -I../Drivers
LDFLAGS=-llua5.2 -lm -lwiringPi -lrt -lm

LUALIB=/usr/lib/lua/5.2

all: brickpi.so

brickpi.so: brickpi.o
	ld brickpi.o -O -lm -shared -o brickpi.so ${LDFLAGS}

brickpi.o: brickpi.c ../Drivers/BrickPi.h ../Drivers/tick.h
	gcc -c brickpi.c ${CFLAGS}

install: brickpi.so
	mkdir -p ${LUALIB}
	install brickpi.so ${LUALIB}

uninstall:
	${LUALIB}/brickpi.so

clean:
	rm -f brickpi.o brickpi.so
