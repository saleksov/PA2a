WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla #-Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFLAGS = -DTEST_MAIN 

SRCS = pa2.c memory.c fileman.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -lm -o pa2

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: pa2
	$(VAL) --leak-check=full --show-leak-kinds=all ./pa2 examples/500_5.txt a.txt b.txt c.txt

testall: test0

# Test all given expected files
test0: pa2
	./pa2 examples/500_5.txt a.txt b.txt c.txt
#diff -w a.txt examples/5.pre
#cmp -l b examples/5.elmore
	
clean: # remove all machine generated files
	rm -f pa2 *.o output? *~ memcheck.txt *.b a.txt b