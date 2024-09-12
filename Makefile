CFLAGS=-Wall -Wextra -std=c11
SOURCES=y.c

target:
	clang $(CFLAGS) $(SOURCES) -o cli && ./cli
