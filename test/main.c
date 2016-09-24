#define _POSIX_C_SOURCE 200809L
#include "ccmd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static ccmd_res_t *cmd_suite(int argc, char **argv) {
	printf("Hello world!\n");
	return ccmd_result(0, NULL);
}

ccmd_def_t commands[] = {
	{ "suite", cmd_suite }
};

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "Usage: ccmd_test cmd (args...)\n");
		return 1;
	}
	ccmd_t *ccmd = ccmd_init(commands, sizeof(commands) / sizeof(ccmd_def_t));
	char *cmd = ccmd_join(argc - 1, argv + 1);
	ccmd_res_t *res = ccmd_exec(ccmd, cmd);
	free(cmd);
	if (!res) {
		fprintf(stderr, "No such command: %s\n", argv[1]);
		return 1;
	}
	if (res->data) {
		printf("Extra data: %s\n", (char *)res->data);
		free(res->data);
	}
	int exit = res->exit;
	free(res);
	return exit;
}
