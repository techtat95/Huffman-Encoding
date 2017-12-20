CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror #-pthread
COVFLAGS = -fprofile-arcs -ftest-coverage
#PROFFLAG = -pg
#DEFINES = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --track-origins=yes --leak-check=full --show-leak-kinds=all  --log-file=
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(DEFINES)
#OBJS = pa15.o 

all: pa15

pa15: pa15.o
	$(GCC) pa15.o -o pa15 -lm

pa15.o: pa15.c huffman.h
	$(GCC) -c pa15.c -o pa15.o

test: pa15
	  echo "Testing filter" ; \
	./pa15 inputs/basic sorted huffman header
inspect: pa15
	./pa15 test.bmp out.bmp
	gcov pa15.c

memory: pa15
	$(VALGRIND)memory ./pa15 inputs/basic sorted huffman header
clean: 
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa15
	/bin/rm -f memory
	/bin/rm -f validate
	/bin/rm -f sorted
	/bin/rm -f huffman
	/bin/rm -f header
