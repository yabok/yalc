/*
 * yalc - Yet Another LolCat
 *
 * Copyright (c) 2015, The yalc developers
 *
 * Distributed under the terms of the ISC license; see the accompanying
 * "LICENSE" file for the full license text.
 */

#include "yalc.h"

int32_t
main (void) {
	setlocale(LC_ALL, "");
	colorized_print(stdin, FOREGROUND);
	return 0;
}

void
colorized_print (FILE *stream, enum plane p) {
	wchar_t line [BUFFER_SIZE];

	for (uint64_t i = 0; fgetws(line, BUFFER_SIZE, stream); i ++) {
		for (uint64_t j = 0; j < wcslen(line); j ++) {
			printf("\x1b[%d8;5;%sm%lc", p, colors[(j/3+i)%22], line[j]);
		}
	}

	printf("\x1b[0m");
}

