CFLAGS = -Wall -g -O2 -std=c99 -I ../include
OBJS = \
	../src/bs.o 	\
	../src/list.o	\
	../src/kv.o	\
	testkv.o

EXEC = \
       testkv


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

all:$(EXEC)

run:$(EXEC)
	@./$(EXEC)

clean:
	$(RM) $(OBJS) $(EXEC)
