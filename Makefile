CC := gcc
YACC := bison
LEX := flex

WARN := -Wall -Werror
INTERNAL_CFLAGS := $(WARN) -std=gnu23 -MMD
override CFLAGS += $(INTERNAL_CFLAGS)

SRC_FILES := $(wildcard *.c) $(wildcard analysis/*.c)
OBJ_FILES := $(SRC_FILES:.c=.o)

all: GoCheck

GoCheck: $(OBJ_FILES) gram.tab.o lex.yy.o
	$(CC) $^ $(CFLAGS) -o $@

lex.yy.o: lex.yy.c gram.tab.h
	$(CC) -c $< $(CFLAGS) -o $@ \
		-Wno-implicit-function-declaration \
		-Wno-unused-function

%.o: %.c gram.tab.h
	$(CC) -c $< $(CFLAGS) -o $@

gram.tab.h: gram.tab.c
gram.tab.c: gram.y gocheck.h
	$(YACC) -d $< -Werror

lex.yy.c: lex.l
	$(LEX) $<

clean: clean-deps clean-objs
	rm -f GoCheck gram.tab.* lex.yy.c

clean-deps:
	rm -f *.d

clean-objs:
	rm -f *.o

-include $(OBJ_FILES:.o=.d)

.PHONY: clean all

