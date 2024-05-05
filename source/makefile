CC				:=gcc
CFLAGS_OBJS		:= -g
OUT				:= mc
LIBS			:= $(wildcard ../libs/*.c)
LIBS_OBJS		:= $(patsubst ../libs/%.c,../libs/%.o,$(LIBS))
SRCS			:= $(filter-out ../source/main.c ../source/demo.c, $(wildcard ../source/*.c))
SRCS_OBJS		:= $(patsubst ../source/%.c,../source/%.o,$(SRCS))
MAIN			:= main.c

$(OUT): $(LIBS_OBJS) $(SRCS_OBJS)
	$(CC) $(CFLAGS_OBJS) $(MAIN) $(LIBS_OBJS) $(SRCS_OBJS) -o $(OUT)

%.c: %.o
	$(CC) $(CFLAGS_OBJS) -o $@.o $< -c $@

clean:
		$(RM) *.o ../libs/*.o *~ $(OUT)