CFLAGS = -Wall -g -O2 -std=c99 -I ../include
OBJS = \
	../src/bs.o \
	../src/list.o\
	testbs.o
EXEC = testbs


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

all:$(EXEC)

run:$(EXEC)
	@./$(EXEC)

clean:
	$(RM) $(OBJS) $(EXEC)
