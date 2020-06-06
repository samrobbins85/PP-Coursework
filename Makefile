all: gameoflife.c libgol.so
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife gameoflife.c -lgol -L.
libgol.so: gol.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -shared -o libgol.so -fPIC gol.c
clean:
	rm -rf gameoflife libgol.so

