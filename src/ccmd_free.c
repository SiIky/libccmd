#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>
#include <string.h>

void ccmd_free(ccmd_t *ccmd) {
	free(ccmd->cmds);
	free(ccmd);
}
