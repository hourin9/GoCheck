CC := gcc
YACC := bison
LEX := flex

WARN := -Wall -Werror
CFLAGS := $(WARN) -std=gnu23

SRC_FILES := $(wildcard *.c)
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
	$(YACC) -d $<

lex.yy.c: lex.l
	$(LEX) $<

clean:
	rm -f *.o *.d GoCheck gram.tab.* lex.yy.c

-include $(OBJ_FILES:.o=.d)

.PHONY: clean all

