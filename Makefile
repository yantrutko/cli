CFLAGS = -Wall -Wextra -std=c23

APPLES = converter.c expenses.c words.c guess.c pch.c xo.c

LIBRARY = library/symbol.c library/line.c library/randigit.c library/time_step.c library/buffer.c library/file_print.c

target:
	clang $(CFLAGS) -o ../cli main.c $(APPLES) $(LIBRARY) && ../cli