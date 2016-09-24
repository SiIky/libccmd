#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>
#include <string.h>

static int ccmd_def_compare(const void *_a, const void *_b) {
	const ccmd_def_t *a = _a;
	const ccmd_def_t *b = _b;
	return strcmp(a->name, b->name);
}

ccmd_res_t *ccmd_exec(ccmd_t *ccmd, const char *command) {
	int argc;
	char **argv = ccmd_split(command, &argc);

	ccmd_def_t key = { argv[0], NULL };
	ccmd_def_t *res = bsearch(&key, ccmd->cmds, ccmd->cmds_len,
		sizeof(ccmd_def_t), ccmd_def_compare);
	if (!res) {
		return NULL;
	}
	return res->handler(argc, argv);
}
