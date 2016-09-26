#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>
#include <string.h>

static int ccmd_def_compare(const void *_a, const void *_b) {
	const ccmd_def_t *a = _a;
	const ccmd_def_t *b = _b;
	return strcmp(a->name, b->name);
}

ccmd_res_t *ccmd_execv(ccmd_t *ccmd, const char *name, char **argv) {
	int argc = 0;
	while (argv[argc]) {
		argc++;
	}

	ccmd_def_t key = { name, NULL };
	ccmd_def_t *res = bsearch(&key, ccmd->cmds, ccmd->cmds_len,
		sizeof(ccmd_def_t), ccmd_def_compare);
	if (!res) {
		return NULL;
	}
	return res->handler(argc, argv);
}
