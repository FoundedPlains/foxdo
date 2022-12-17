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

CC = gcc
CFLAGS = -O2 -Wall -D_GNU_SOURCE
OBJ = rootize.o launch.o timeout.o

.DEFAULT_GOAL = all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	ar rcs ../libfoxdo.a $(OBJ)

clean:
	rm ../libfoxdo.a
	rm *.o