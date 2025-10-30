WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla #-Werror
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR)
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
test0: pa2
	./pa2 examples/500_5.txt 1.txt 2.txt 3.txt 4.txt
	diff -w 4.txt pa2_outputs/500_leafs/out_file4
#cmp -l b examples/5.elmore
	
clean: # remove all machine generated files
	rm -f pa2 *.o output? *~ memcheck.txt *.b *.txt b