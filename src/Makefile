CC = gcc
CFLAGS = -Wall -I/usr/include/ -I.
LDFLAGS = -lncurses 
DEPS = conway.h
OBJ = main.o init.o

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

conway: $(OBJ)
	${CC}  -o $@ $^  $(LDFLAGS) $(CFLAGS)

clean:
	rm -f *.o ${BINS} 
