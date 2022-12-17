# foxdo - suckless sudo/doas
# Copyright (C) <year>  <name of author>

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
	$(CC) $(CFLAGS) -L. -lcrypt  main.c -o main -lfoxstd -lfoxdo

rootable:
	sudo chown root:root ./main
	sudo chmod ugo= ./main
	sudo chmod +s ./main
	sudo chmod u+rwx,g=rx,o=rx ./main

install: rootable
	sudo cp -p main /usr/bin/foxdo
	sudo cp defconf.foxconfig /etc/foxdo.foxconfig

uninstall:
	sudo rm /usr/bin/foxdo
	sudo rm /etc/foxdo.foxconfig

clean:
	$(MAKE) -C foxstd clean
	$(MAKE) -C src clean
	rm -f main
	rm foxstd.h libfoxstd.a