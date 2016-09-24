#pragma once

typedef struct ccmd_def ccmd_def_t;
typedef struct ccmd ccmd_t;

struct ccmd {
	int cmds_len;
	ccmd_def_t *cmds;
};
