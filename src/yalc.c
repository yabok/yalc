/*
 * yalc - Yet Another LolCat
 *
 * Copyright (c) 2015, The yalc developers
 *
 * Distributed under the terms of the ISC license; see the accompanying
 * "LICENSE" file for the full license text.
 */

#include "yalc.h"

const char * argp_program_version = "yalc 0.0.3";
const char * argp_program_bug_address = "https://github.com/yabok/yalc/issues";
static char * doc = "yalc -- a minimalist lolcat clone in C";

static error_t
parse_opt (int32_t, char *, struct argp_state *);

int32_t
main (int32_t argc, char * argv []) {
	if ( argc <= 1 ) {
		fprintf(stderr, "See `%s --help` for more information\n", argv[0]);
		return EXIT_FAILURE;
	}

	setlocale(LC_ALL, "");

	const struct argp_option os [] = {
		{ 0,        0,   0,      0, "Options:",                      -1 },
		{ "stream", 's', "FILE", 0, "Colorize file ('-' for stdin)", 0  },
		{ "fg",     'f', 0,      0, "Colorize foreground (default)", 0  },
		{ "FG",     'F', 0,      0, "Do not colorize foreground",    0  },
		{ "bg",     'b', 0,      0, "Colorize background",           0  },
		{ "BG",     'B', 0,      0, "Do not colorize background",    0  },
		{ 0,        0,   0,      0, 0,                               0  }
	};

	struct argp argp = { os, parse_opt, "", doc, NULL, NULL, 0 };
	struct args args = { true, false, 0 };

	argp_parse(&argp, argc, argv, 0, 0, &args);

	if ( !args.scount ) {
		fputs("You must pass at least one stream to lol\n", stderr);
		return EXIT_FAILURE;
	} return EXIT_SUCCESS;
}

void
colorized_print (FILE * stream, struct args * a) {
	wchar_t line [BUFFER_SIZE];

	for ( uint64_t i = 0; fgetws(line, BUFFER_SIZE, stream); i ++ ) {
		for ( uint64_t j = 0; j < wcslen(line); j ++ ) {
			printf("%s%s%s%s%s%s%lc", a->fg ? "\x1b[38;5;"       : "",
									  a->fg ? colors[(j/3+i)%22] : "",
									  a->fg ? "m"                : "",
									  a->bg ? "\x1b[48;5;"       : "",
									  a->bg ? colors[(j+i)%22]   : "",
									  a->bg ? "m"                : "",
									  line[j]);
		}
	}

	printf("\x1b[0m");
}

static error_t
parse_opt (int32_t key, char * arg, struct argp_state * state) {
	struct args * args = state->input;
	switch ( key ) {
		case 's':
			if ( strncmp(arg, "-", 2) ) {
				FILE * file = fopen(arg, "r");
				if ( file ) {
					colorized_print(file, args);
					fclose(file);
				} else {
					fputs("Failed to open file correctly\n", stderr);
				}
			} else {
				colorized_print(stdin, args);
			} args->scount ++; break;

		case 'f':
			args->fg = true; break;

		case 'F':
			args->fg = false; break;

		case 'b':
			args->bg = true; break;

		case 'B':
			args->bg = false; break;

		default:
			return ARGP_ERR_UNKNOWN;
	}

	return EXIT_SUCCESS;
}

