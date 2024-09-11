CFLAGS=-Wall -Wextra -std=c23
SOURCES=y.c

target:
	clang $(CFLAGS) $(SOURCES) -o cli && ./cli
