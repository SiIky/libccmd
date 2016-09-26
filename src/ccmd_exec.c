#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>
#include <string.h>

ccmd_res_t *ccmd_exec(ccmd_t *ccmd, const char *command) {
	int argc;
	char **argv = ccmd_split(command, &argc);
	ccmd_res_t *res = ccmd_execv(ccmd, argv[0], argv);
	ccmd_argv_free(argc, argv);
	return res;
}
