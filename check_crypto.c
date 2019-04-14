#include "check_crypto.h"

config *create(const int n)
{
	config *head, *node, *end;
	int i;

	head = (config*)malloc(sizeof(config));
	end  = head;
	for (i = 0; i < n; i++) {
		node = (config*)malloc(sizeof(config));

		end->next = node;
		end = node;
	}
	end->next = NULL;
	return head;
}


void change(config *list, const int n, config *crypto)
{
	config *tmp = list;
	int i = 0;

	while (i < n && tmp != NULL) {
		tmp = tmp->next;
		i++;
	}

	if (tmp != NULL) {
		/* do something */
		strcpy(tmp->hash_path, crypto->hash_path);
		strcpy(tmp->export_path, crypto->export_path);
		strcpy(tmp->mount, crypto->mount);
		strcpy(tmp->mount_path, crypto->mount_path);
		strcpy(tmp->total_space, crypto->total_space);
		strcpy(tmp->free_space, crypto->free_space);
	} else {
		puts("nothing to change");
	}
}


void delete_dat(config *crypto, const int n)
{
	config *tmp = crypto, *pre_n;
	int i = 0;

	while (i < n && tmp != NULL) {
		pre_n = tmp;
		tmp = tmp->next;
		i++;
	}

	if (tmp != NULL) {
		pre_n->next = tmp->next;
		free(tmp);
	} else {
		puts("node is not exist");
	}
}


void insert(config *crypto, const int n)
{
	config *tmp = crypto, *insert_dat;
	int i = 0;

	while (i < n && tmp != NULL) {
		tmp = tmp->next;
		i++;
	}

	if (tmp != NULL) {
		insert_dat = (config*)malloc(sizeof(config));
		// do something
		insert_dat = tmp->next;
		tmp->next = insert_dat;
	} else {
		puts("node is not exist");
	}
}


void print(config *head)
{
	while (head->next != NULL) {
		head = head->next;
		printf("%s\n", head->hash_path);
		printf("%s\n", head->export_path);
		printf("%s\n", head->mount);
		printf("%s\n", head->mount_path);
		printf("%s\n", head->total_space);
		printf("%s\n", head->free_space);
	}
	
}


/* get crypto number */
int number_crypto(const char *file_path)
{
	int cnt = 0;
	FILE *fp;
	char line[512];

	fp = fopen(file_path, "r");
	if (fp) {
		while (fgets(line, 512, fp) != NULL) {
			if (line[0] == '[') {
				cnt++;
				/* printf("%s\n", line); */
			}
		}

	} else {
		puts("can't open the config file");
	}

	fclose(fp);

	return cnt - 1;
}



int read_file(const char *file_path, config *head)
{
	int cnt = 0;
	int crypto_n = 0;
	int cnt_line = 0;
	/* int case_line = 0; */
	FILE *fp;
	char line[511];
	config crypto_block;

	fp = fopen(file_path, "r");
	if (!fp) {
		puts("can't open the config file");

	}

	while (fgets(line, 511, fp) != NULL) {
		/* find first crypto entry */
		if (line[0] == '[') {
			cnt++;
			if (cnt == 2) {
				cnt_line = 1;
			}

		}
		
		if (line[0] =='[' && cnt == 1) {
			cnt_line = 1;
		}

		if (cnt_line > 0 ) {
			/* case_line = cnt_line % 7; */
			switch (cnt_line % 7) {
				case 1 : strcpy(crypto_block.hash_path, line);
					break;
				case 2 : strcpy(crypto_block.export_path, line);
					break;
				case 3 : strcpy(crypto_block.mount, line);
					break;
				case 4 : strcpy(crypto_block.mount_path, line);
					break;
				case 5 : strcpy(crypto_block.total_space, line);
					break;
				case 6 : strcpy(crypto_block.free_space, line);
					break;
				case 0 :
					crypto_n++;
					change(head, crypto_n, &crypto_block);
					break;
				default : break;
			}
			cnt_line++;
		}

	}

	fclose(fp);

	return cnt_line;
}
