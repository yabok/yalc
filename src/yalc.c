/*
 * yalc - Yet Another LolCat
 *
 * Copyright (c) 2015, The yalc developers
 *
 * Distributed under the terms of the ISC license; see the accompanying
 * "LICENSE" file for the full license text.
 */

#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define BUFFER_SIZE 5000

static const char *colors [] = {
	"88", "124", "160", "196", "202", "208", "214", "184", "190",
	"154", "118", "82", "76", "34", "30", "27", "93", "129", "165",
	"128", "127", "125"
};

int32_t
main (void) {
	setlocale(LC_ALL, "");
	wchar_t line [BUFFER_SIZE];

	for (uint64_t i = 0; fgetws(line, BUFFER_SIZE, stdin) != NULL; i ++ ) {
		for (uint64_t j = 0; j < wcslen(line); j ++ ) {
			printf("\x1b[38;5;%sm%lc", colors[(j/3+i)%22], line[j]);
		}
	}

	printf("\x1b[0m");

	return 0;
}
