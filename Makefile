CFLAGS = -Wall -Wextra -std=c23

LIBRARY = \
library/symbol.c \
library/line.c \
library/randigit.c \
library/time_step.c \
library/buffer.c \
library/file_print.c

APPLES = \
main.c \
converter.c \
expenses.c \
words.c \
guess.c \
pch.c \
xo.c

pie:
	clang $(CFLAGS) -o ../cli $(APPLES) $(LIBRARY) && ../cli
