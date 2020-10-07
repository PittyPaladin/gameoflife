CC = gcc
CFLAGS = -Wall -I/usr/include/ -I.
LDFLAGS = -lncurses 
DEPS = golcompute.h goldisp.h # add header files here
SOURCES = golutils.c dispcells.c main.c # add source files here
OBJECTS = $(SOURCES:.c=.o)
BUILDIR = ../build
EXECUTABLE = $(BUILDIR)/gameoflife

$(BUILDIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(BUILDIR)/$(OBJECTS)
	gcc  -o $@ $^  $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJECTS) conway 
