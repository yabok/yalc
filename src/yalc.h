/*
 * yalc - Yet Another LolCat
 *
 * Copyright (c) 2015, The yalc developers
 *
 * Distributed under the terms of the ISC license; see the accompanying
 * "LICENSE" file for the full license text.
 */

#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <argp.h>

#define BUFFER_SIZE 5000

struct args {
	uint16_t fg: 1, bg: 1, scount: 14;
};

static const char *colors [] = {
	"88", "124", "160", "196", "202", "208", "214", "184", "190",
	"154", "118", "82", "76", "34", "30", "27", "93", "129", "165",
	"128", "127", "125"
};

void
colorized_print (FILE *stream, struct args * a);

