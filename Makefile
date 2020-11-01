CC = gcc
CFLAGS = -Wall -I/usr/include/ -I.
LDFLAGS = -lncurses 
DEPS = src/goldisp.h src/golcompute.h
OBJ = build/main.o build/disp.o build/golutils.c
EXEC = bin/gameoflife

# $(EXEC): $(OBJ)
# 	$(CC) -o $@ $^  $(LDFLAGS) $(CFLAGS)

# %.o: src/%.c $(DEPS)
# 	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXEC)

$(EXEC): build/main.o build/disp.o build/golutils.o 
	$(CC) -o $(EXEC) build/main.o build/disp.o build/golutils.o $(LDFLAGS) $(CFLAGS)

build/main.o: src/main.c src/golcompute.h src/goldisp.h
	$(CC) -c $< -o $@

build/disp.o: src/disp.c src/golcompute.h
	$(CC) -c $< -o $@

build/golutils.o: src/golutils.c
	$(CC) -c $< -o $@

clean:
	rm -f build/* $(EXEC) 
