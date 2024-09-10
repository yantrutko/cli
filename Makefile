CFLAGS=-Wall -Wextra -std=c23
SOURCES=c.c

target:
	clang $(CFLAGS) $(SOURCES) -o c && ./c
