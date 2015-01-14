CC := clang
CFLAGS += -std=c11 -g -O2 -fstack-protector-all -fpie -pie -Wl,-z,relro,-z,now -ggdb -Weverything

all: yalc

yalc: src/yalc.c
	$(CC) $(CFLAGS) -o $@ src/yalc.c

.PHONY: all
