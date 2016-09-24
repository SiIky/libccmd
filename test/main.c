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
	char *joined = strdup(argv[1]);
	for (int i = 2; i < argc; ++i) {
		char *new = malloc(strlen(joined) + strlen(argv[i]) + 2);
		strcpy(new, joined);
		strcat(new, " ");
		strcat(new, argv[i]);
		free(joined);
		joined = new;
	}
	ccmd_res_t *res = ccmd_exec(ccmd, joined);
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
	free(joined);
	return exit;
}
