CC=gcc

CFLAGS=-Wall -Wextra -Werror -Wshadow -std=c99 -pedantic -g -fwrapv

.PHONY: sloth
default: sloth

sloth: slothvm.c sloth.c
	$(CC) $(CFLAGS) -o sloth sloth.c slothvm.c lib/throw.c lib/stack.c parser.c $(CFLAGSEXTRA)

test: slothvm.c tests.c
	$(CC) $(CFLAGS) -o slothTest tests.c slothvm.c lib/throw.c lib/stack.c parser.c $(CFLAGSEXTRA)

clean:
	rm -Rf sloth

cleanTest:
	rm -Rf slothTest