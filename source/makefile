CC				:=gcc
CFLAGS_OBJS		:= -g
OUT				:= cc
LIBS			:= $(filter-out ../libs/Regex.c ../libs/StateMachine.c , $(wildcard ../libs/*.c))
LIBS_OBJS		:= $(patsubst ../libs/%.c,../libs/%.o,$(LIBS))
SEMANTICS		:= $(wildcard ../grammar/*.c)
SEMANTICS_OBJS	:= $(patsubst ../grammar/%.c,../grammar/%.o,$(SEMANTICS))
SRCS			:= $(filter-out ../source/Construction.c ../source/Lexer.c ../source/Parser.c ../source/CodeGenerator.c ../source/main.c ../source/demo.c, $(wildcard ../source/*.c))
SRCS_OBJS		:= $(patsubst ../source/%.c,../source/%.o,$(SRCS))
MAIN			:= main.c

$(OUT): $(LIBS_OBJS) $(SRCS_OBJS) $(SEMANTICS_OBJS)
	$(CC) $(CFLAGS_OBJS) $(MAIN) $(LIBS_OBJS) $(SRCS_OBJS) $(SEMANTICS_OBJS) -o $(OUT)

%.c: %.o
	$(CC) $(CFLAGS_OBJS) -o $@.o $< -c $@

clean:
		$(RM) *.o ../libs/*.o *~