CC := clang
CFLAGS += -std=c11 -O2 -fstack-protector-all -fpie -pie -Weverything -Wno-disabled-macro-expansion -Wl,-z,relro,-z,now -ggdb

all: yalc

yalc: src/yalc.c
	$(CC) $(CFLAGS) -o $@ src/yalc.c

.PHONY: all
