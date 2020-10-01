CC = gcc
CFLAGS = -Wall -I/usr/include/ -I.
LDFLAGS = -lncurses 
DEPS = conway.h # add header files here
SOURCES = init.c main.c # add source files here
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = gameoflife

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(OBJECTS)
	gcc  -o $@ $^  $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJECTS) conway 

#c