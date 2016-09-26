#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

ccmd_res_t *ccmd_execl(ccmd_t *ccmd, const char *name, ...) {
	va_list ap;
	int argc = 0;
	int arglen = 32;
	char **argv = malloc(arglen * sizeof(char *));

	va_start(ap, name);
	char *arg;
	do {
		arg = va_arg(ap, char *);
		argv[argc] = arg;
		if (argc == arglen) {
			arglen *= 2;
			char **argvng = realloc(argv, arglen * sizeof(char *));
			if (!argvng) {
				ccmd_argv_free(argc, argv);
				return NULL;
			}
			argv = argvng;
		}
	} while(arg);
	va_end(ap);

	ccmd_res_t *res = ccmd_execv(ccmd, name, argv);
	ccmd_argv_free(argc, argv);
	return res;
}
