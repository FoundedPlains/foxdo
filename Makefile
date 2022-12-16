CC ?= gcc
CFLAGS ?= -Wall -g -O2

.DEFAULT_GOAL = all

all:
	@echo "CONFIG_FOXAUTH=y" > foxstd/.config
	$(MAKE) -C foxstd all
	cp foxstd/foxstd.h .
	cp foxstd/libfoxstd.a .
	$(MAKE) -C src all
	$(CC) $(CFLAGS) -L. -lcrypt  main.c -o main -lfoxstd -lfoxdo

rootable:
	sudo chown root:root ./main
	sudo chmod ugo= ./main
	sudo chmod +s ./main
	sudo chmod u+rwx,g=rx,o=rx ./main

install: rootable
	sudo cp -p main /usr/bin/foxdo

clean:
	$(MAKE) -C foxstd clean
	$(MAKE) -C src clean
	rm main
	rm foxstd.h libfoxstd.a