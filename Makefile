CC := clang
CFLAGS += -std=c11 -ggdb -Weverything

all: yalc

yalc: src/yalc.c
	$(CC) $(CFLAGS) -o $@ src/yalc.c

.PHONY: all
