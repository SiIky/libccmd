#include "ccmd.h"
#include <stdlib.h>

ccmd_res_t *ccmd_result(int exit, void *data) {
	ccmd_res_t *res = malloc(sizeof(ccmd_res_t));
	res->exit = exit;
	res->data = data;
	return res;
}
