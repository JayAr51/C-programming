CC=gcc
CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
poker: cards.c deck.c eval.c future.c input.c main.c 
	gcc -o poker $(CFLAGS) $^
clean:
	rm -f test poker test-eval *~ vg*

