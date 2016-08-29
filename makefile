CC=gcc
LDFLAGS=-lncurses
PROG=mandelbrot

all:
	$(CC) mandelbrot.c -o $(PROG) $(LDFLAGS)

test: $(PROG)
	./$(PROG)

clean:
	rm -rf $(PROG)
