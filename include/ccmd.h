/* This file is part of libccmd.  */

#pragma once

typedef struct ccmd_def ccmd_def_t;
typedef struct ccmd_res ccmd_res_t;
typedef struct ccmd ccmd_t;

struct ccmd_def {
	const char *name;
	ccmd_res_t *(*handler)(int argc, char **argv);
};

struct ccmd_res {
	int exit;
	void *data;
};

/*
 * Initializes a command handler with the given list of available commands.
 */
ccmd_t *ccmd_init(const ccmd_def_t commands[], int len);

/*
 * Parses and executes a command and returns the result. Returns NULL if the
 * command cannot be executed.
 */
ccmd_res_t *ccmd_exec(ccmd_t *ccmd, const char *cmd);

/*
 * Helper function that creates a ccmd_res_t for you. This can simply be passed
 * to free, but you're responsible for freeing whatever 'data' is.
 */
ccmd_res_t *ccmd_result(int exit, void *data);