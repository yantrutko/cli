CFLAGS = -Wall -Wextra -pedantic -std=c23

SOURCES := $(shell find -name '*.c')

cli:
	clang $(CFLAGS) -o ../cli $(SOURCES) && ../cli
