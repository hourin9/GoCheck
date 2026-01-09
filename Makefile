CC := gcc

WARN := -Wall -Werror
CFLAGS := $(WARN) -std=c23

SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(SRC_FILES:.c=.o)

all: GoCheck

GoCheck: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(CFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f *.o *.d GoCheck

-include $(OBJ_FILES:.o=.d)

.PHONY: clean all

