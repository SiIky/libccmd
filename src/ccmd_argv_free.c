#include "ccmd.h"
#include "ccmd_t.h"
#include <stdlib.h>

void ccmd_argv_free(int argc, char **argv) {
	while (argc--) {
		free(argv[argc]);
	}
	free(argv);
}
