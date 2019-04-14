#ifndef CHECK_CRYPTO
#define CHECK_CRYPTO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct config {
	char hash_path[512];
	char export_path[512];
	char mount[512];
	char mount_path[512];
	char total_space[512];
	char free_space[512];
	struct config *next;
} config;

config *create(const int n);
void change(config *list, const int n, config *crypto);
void delete_dat(config *crypto, const int n);
void insert(config *crypto, const int n);
void print(config *head);

/* How many crypto in config_file */
int number_crypto(const char *file_path);

int read_file(const char *file_path, config *head);

#endif
