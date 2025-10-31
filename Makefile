WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla #-Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFLAGS = -DTEST_MAIN 

SRCS = pa2.c memory.c fileman.c DPfunc.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -lm -o pa2

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa2
	$(VAL) --leak-check=full --show-leak-kinds=all ./pa2 examples/500_5.txt a.txt b.txt c.txt d.txt

testall: test0

# Test all given expected files
test3: pa2
	./pa2 examples/3.txt 1.txt 2.txt 3.txt 4.txt
	diff -w 4.txt examples/3_all.pck

test8: pa2
	./pa2 examples/8.txt 1.txt 2.txt 3.txt 4.txt
	diff -w 4.txt examples/8_all.pck

test10: pa2
	./pa2 examples/10_1.txt 1.txt 2.txt 3.txt 4.txt
	diff -w 3.txt pa2_outputs/10_leafs/out_file3
	diff -w 4.txt pa2_outputs/10_leafs/out_file4

test100: pa2
	./pa2 examples/100_3.txt 1.txt 2.txt 3.txt 4.txt
	diff -w 3.txt pa2_outputs/100_leafs/out_file3
	diff -w 4.txt pa2_outputs/100_leafs/out_file4

test500: pa2
	./pa2 examples/500_5.txt 1.txt 2.txt 3.txt 4.txt
	diff -w 3.txt pa2_outputs/500_leafs/out_file3
	diff -w 4.txt pa2_outputs/500_leafs/out_file4
	
clean: # remove all machine generated files
	rm -f pa2 *.o output? *~ memcheck.txt *.b *.txt b