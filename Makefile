CFLAGS = -Wall -pedantic -std=c23

SOURCES := $(shell find -name '*.c')

demo-cli:
	clang $(CFLAGS) -o ../demo-cli $(SOURCES) && cp -r --update=none ./demo-lines ../ && ../demo-cli
