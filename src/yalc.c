/*
 * yalc - Yet Another LolCat
 *
 * Copyright (c) 2015, The yalc developers
 *
 * Distributed under the terms of the ISC license; see the accompanying
 * "LICENSE" file for the full license text.
 */

#include "yalc.h"

struct args {
	enum plane p;
};

const char * argp_program_version = "yalc 0.0.2";
const char * argp_program_bug_address = "https://github.com/yabok/yalc/issues";
static char * doc = "yalc -- a minimalistic lolcat clone in C";

static error_t
parse_opt (int32_t, char *, struct argp_state *);

int32_t
main (int32_t argc, char * argv []) {
	if ( argc <= 1 ) {
		fprintf(stderr, "See `%s --help` for more information\n", argv[0]);
	}

	setlocale(LC_ALL, "");

	struct argp_option os [] = {
		{ 0,      0,   0,      0, "Options:",                      -1 },
		{ "file", 'f', "FILE", 0, "Colorize file ('-' for stdin)", 0  },
		{ "fg",   'F', 0,      0, "Colorize foreground (default)", 0  },
		{ "bg",   'B', 0,      0, "Colorize background",           0  },
		{ 0,      0,   0,      0, 0,                               0  }
	};

	struct argp argp = { os, parse_opt, "", doc, NULL, NULL, 0 };
	struct args args = { FOREGROUND };

	argp_parse(&argp, argc, argv, 0, 0, &args);

	return 0;
}

void
colorized_print (FILE * stream, enum plane p) {
	wchar_t line [BUFFER_SIZE];

	for ( uint64_t i = 0; fgetws(line, BUFFER_SIZE, stream); i ++ ) {
		for ( uint64_t j = 0; j < wcslen(line); j ++ ) {
			printf("\x1b[%d8;5;%sm%lc", p, colors[(j/3+i)%22], line[j]);
		}
	}

	printf("\x1b[0m");
}

static error_t
parse_opt (int32_t key, char * arg, struct argp_state * state) {
	struct args * args = state->input;
	switch ( key ) {
		case 'f':
			if ( strncmp(arg, "-", 2) != 0 ) {
				FILE * file = fopen(arg, "r");
				if ( file ) {
					colorized_print(file, args->p);
					fclose(file);
				} else {
					fputs("Failed to open file correctly\n", stderr);
				}
			} else {
				colorized_print(stdin, args->p);
			} break;

		case 'F':
			args->p = FOREGROUND; break;

		case 'B':
			args->p = BACKGROUND; break;

		default:
			return ARGP_ERR_UNKNOWN;
	} return 0;
}

