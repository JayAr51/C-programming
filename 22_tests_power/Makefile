CFLAGS=-ggdb3 -Wall -Werror -std=gnu99
test-power: power.o test-power.o
	gcc $(CFLAGS) -c power.c
	gcc $(CFLAGS) -c test-power.c
	gcc -o test-power -ggdb3 -pedantic -std=gnu99 -Wall -Werror test-power.o power.o

clean:
	rm test-power *~
