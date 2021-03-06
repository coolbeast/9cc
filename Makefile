CFLAGS = -Wall -std=c11
SRCS = $(wildcard *.c)
OBJS = $(SRCS: .c=.o)

9cc:	$(OBJS)
	gcc -o 9cc $(OBJS) $(CFLAGS)
$(OBJS):	9cc.h

test:	9cc
	./test.sh

clean:
	rm -f 9cc *.o *~ tmp*
