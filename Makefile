CFLAGS = -Wall -pedantic

SOURCES := $(shell find -name '*.c')

LINES = cp -r --update=none dlines ../

democli:
	clang $(CFLAGS) -o ../democli $(SOURCES) && $(LINES) && ../democli
