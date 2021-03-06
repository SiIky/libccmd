/* This file is part of libccmd */

#pragma once

#include <stdarg.h>

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
 * Useful macro for calling ccmd_init:
 *
 * const ccmd_def_t commands[10];
 * ccmd_init(ccmds(commands));
 */
#define ccmds(arr) arr, sizeof(arr) / sizeof(ccmd_def_t)

/*
 * Initializes a command handler with the given list of available commands.
 */
ccmd_t *ccmd_init(const ccmd_def_t commands[], int len);

/*
 * Frees a command handler.
 */
void ccmd_free(ccmd_t *ccmd);

/*
 * Parses and executes a command and returns the result. Returns NULL if the
 * command cannot be executed.
 */
ccmd_res_t *ccmd_exec(ccmd_t *ccmd, const char *cmd);

/*
 * Executes a command and returns the result. Returns NULL if the command cannot
 * be executed. Set the last argument to NULL.
 */
ccmd_res_t *ccmd_execv(ccmd_t *ccmd, const char *name, char **argv);

/*
 * Executes a command and returns the result. Returns NULL if the command cannot
 * be executed. Set the last argument to NULL.
 */
ccmd_res_t *ccmd_execl(ccmd_t *ccmd, const char *name, ...);

/*
 * Helper function that creates a ccmd_res_t for you. This can simply be passed
 * to free, but you're responsible for freeing whatever 'data' is.
 */
ccmd_res_t *ccmd_result(int exit, void *data);

/*
 * Splits a string into an argument vector.
 */
char **ccmd_split(const char *cmd, int *argc);

/*
 * Joins an argument vector into one string.
 */
char *ccmd_join(int argc, char **argv);

/*
 * Frees an argument vector.
 */
void ccmd_argv_free(int argc, char **argv);
