#include "ccmd.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char whitespace[] = " \f\n\r\t\v";

char **ccmd_split(const char *cmd, int *argc) {
	*argc = 0;
	int alloc = 2;
	char **argv = malloc(sizeof(char *) * alloc);
	bool in_token = false;
	bool in_string = false;
	bool in_char = false;
	bool escaped = false;
	const char *end = cmd;
	if (cmd) {
		while (*cmd) {
			if (!in_token) {
				cmd = (end += strspn(end, whitespace));
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
			if (end - cmd > 0) {
				char *token = malloc(end - cmd + 1);
				strncpy(token, cmd, end - cmd + 1);
				token[end - cmd] = '\0';
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
