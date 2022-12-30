# foxdo - suckless sudo/doas
# Copyright (C) 2022 Ján Gajdoš

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

CC ?= gcc
CFLAGS ?= -Wall -g -O2

.DEFAULT_GOAL = all

all:
	@echo "CONFIG_FOXAUTH=y" > foxstd/.config
	@echo "CONFIG_FOXCONFIG=y" >> foxstd/.config
	$(MAKE) -C foxstd all
	cp foxstd/foxstd.h .
	cp foxstd/libfoxstd.a .
	$(MAKE) -C src all
	$(CC) $(CFLAGS) main.c -o main -L. -lfoxdo -lcrypt -lfoxstd

rootable:
	chown root:root ./main
	chmod ugo= ./main
	chmod +s ./main
	chmod u+rwx,g=rx,o=rx ./main

install: rootable
	cp -p main /usr/bin/foxdo
	cp defconf.foxconfig /etc/foxdo.foxconfig

uninstall:
	rm /usr/bin/foxdo
	rm /etc/foxdo.foxconfig

clean:
	$(MAKE) -C foxstd clean
	$(MAKE) -C src clean
	rm -f main
	rm foxstd.h libfoxstd.a