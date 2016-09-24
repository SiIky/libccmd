#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>
#include <string.h>

static int ccmd_cmp(const void *_a, const void *_b) {
	ccmd_def_t *const *a = _a;
	ccmd_def_t *const *b = _b;
	return strcmp((*a)->name, (*b)->name);
}

ccmd_t *ccmd_init(const ccmd_def_t commands[], int len) {
	ccmd_t *c = calloc(1, sizeof(ccmd_t));
	if (!c) {
		return NULL;
	}
	c->cmds_len = len;
	c->cmds = calloc(len, sizeof(ccmd_def_t));
	if (!c->cmds) {
		free(c);
		return NULL;
	}
	memcpy(c->cmds, commands, len * sizeof(ccmd_def_t));
	qsort(c->cmds, len, sizeof(ccmd_def_t), ccmd_cmp);
	return c;
}
