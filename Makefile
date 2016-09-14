CFLAGS = -O2 -g -std=c99 -Wall -I include

OUT = bin
EXEC = $(OUT)/csina
OBJS = \
       src/kv.o \
       src/list.o\
       src/request.o \
       src/response.o\
       src/server.o \
       src/bs.o \
       src/app.o


deps := $(OBJS:%.o=%.o.d)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -MMD -MF $@.d -c $<

$(EXEC): $(OBJS)
	mkdir -p $(OUT)
	$(CC) $(OBJS) -o $@

all: $(EXEC)
run: $(EXEC)
	@./$(EXEC) $(port)

clean:
	$(RM) $(OBJS) $(deps) $(EXEC)

-include $(deps)
