#include "ccmd.h"
#include "ccmd_t.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char whitespace[] = " \f\n\r\t\v";

static char **split_args(const char *start, int *argc) {
	*argc = 0;
	int alloc = 2;
	char **argv = malloc(sizeof(char *) * alloc);
	bool in_token = false;
	bool in_string = false;
	bool in_char = false;
	bool escaped = false;
	const char *end = start;
	if (start) {
		while (*start) {
			if (!in_token) {
				start = (end += strspn(end, whitespace));
				in_token = true;
			}
			if (*end == '"' && !in_char && !escaped) {
				in_string = !in_string;
			} else if (*end == '\'' && !in_string && !escaped) {
				in_char = !in_char;
			} else if (*end == '\\') {
				escaped = !escaped;
			} else if (*end == '\0' || (!in_string && !in_char &&
						!escaped && strchr(whitespace, *end))) {
				goto add_token;
			}
			if (*end != '\\') {
				escaped = false;
			}
			++end;
			continue;
add_token:
			if (end - start > 0) {
				char *token = malloc(end - start + 1);
				strncpy(token, start, end - start + 1);
				token[end - start] = '\0';
				argv[*argc] = token;
				if (++*argc + 1 == alloc) {
					argv = realloc(argv, (alloc *= 2) * sizeof(char *));
				}
			}
			in_token = false;
			escaped = false;
		}
	}
	argv[*argc] = NULL;
	return argv;
}

static int ccmd_def_compare(const void *_a, const void *_b) {
	const ccmd_def_t *a = _a;
	const ccmd_def_t *b = _b;
	return strcmp(a->name, b->name);
}

ccmd_res_t *ccmd_exec(ccmd_t *ccmd, const char *command) {
	int argc;
	char **argv = split_args(command, &argc);

	ccmd_def_t key = { argv[0], NULL };
	ccmd_def_t *res = bsearch(&key, ccmd->cmds, ccmd->cmds_len,
		sizeof(ccmd_def_t), ccmd_def_compare);
	if (!res) {
		return NULL;
	}
	return res->handler(argc, argv);
}
