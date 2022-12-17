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