CC = gcc
CFLAGS = -O2 -Wall
OBJ = rootize.o launch.o

.DEFAULT_GOAL = all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ)
	ar rcs ../libfoxdo.a $(OBJ)

clean:
	rm ../libfoxdo.a
	rm *.o