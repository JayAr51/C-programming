CFLAGS=-ggdb3 -Wall -Werror -std=gnu99
test: maxSeq.o test-subseq.o
	gcc $(CFLAGS) -c maxSeq.c 
	gcc $(CFLAGS) -c test-subseq.c
	gcc -o test maxSeq.o test-subseq.o
clean:
	rm test *~
