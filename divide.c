#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int buf_size = 8192;
	char buf[buf_size];
	char name[4096] = "/home/tao/crypto/powershell/log/py_log";
	char path[4096] = "/home/tao/crypto/powershell/log/py_log_div";
	char *file_log;
	int fd, fd_tmp, read_size, twenty_m = 0, num = 1;
	struct stat st;
	off_t unread_size = 0;
	int name_len;

	int len = snprintf(NULL, 0, "%d", num);
	char *str_num = malloc(len + 1);


	if (argc == 2) {
		strncpy(name, argv[1], 4096);
		strncpy(path, argv[1], 4096);

		file_log = strrchr(name, '/');
		strncat(path, "_div", strlen("_div"));
		if (mkdir(path, 0744) == -1) {
			perror(path);
			exit(EXIT_FAILURE);
		}
		strncat(path, file_log, 4096);
		name_len = strlen(path);
	} else if (argc == 3) {
		strncpy(name, argv[1], 4096);
		strncpy(path, argv[2], 4096);

		file_log = strrchr(name, '/');
		if (access(path, R_OK | W_OK | X_OK) == -1) {
			perror(path);
			exit(EXIT_FAILURE);
		}
		strncat(path, file_log, 4096);
		name_len = strlen(path);
	}

	if ( (fd = open(name, O_RDONLY)) == -1) {
		perror(name);
		exit(EXIT_FAILURE);
	}


	snprintf(str_num, len + 1, "%d", num);
	strncat(path, str_num, len + 1);
	if ( (fd_tmp = open(path, O_RDWR | O_CREAT, 0644)) == -1){
		perror(name);
		exit(EXIT_FAILURE);
	}

	if ( (fstat(fd, &st)) == -1) {
		perror("get property failed");
		exit(EXIT_FAILURE);
	}
	unread_size = st.st_size;
	if (st.st_size < buf_size) {
		buf_size = st.st_size;
	}
	while (unread_size > 0) {
		if (twenty_m == 2560) {	/* 20*1024*1024/8192 == 2560 */
			free(str_num);
			close(fd_tmp);
			num++;
			path[name_len] = '\0';

			len = snprintf(NULL, 0, "%d", num);
			str_num = malloc(len + 1);
			snprintf(str_num, len + 1, "%d", num);
			strncat(path, str_num, len + 1);

			if ( (fd_tmp = open(path, O_RDWR
						| O_CREAT, 0644)) == -1){
				perror(name);
				exit(EXIT_FAILURE);
			}

			twenty_m = 0;
		}


		if ( unread_size < buf_size) {
			buf_size = unread_size;
		}
		
		if ( (read_size = read(fd, buf, buf_size)) == -1) {
			perror("read filed");
			exit(EXIT_FAILURE);
		}

		if (write(fd_tmp, buf, buf_size) == -1) {
			perror("write error");
			exit(EXIT_FAILURE);
		}

		twenty_m++;
		unread_size -= buf_size;
	}

	

	free(str_num);
	close(fd);
	close(fd_tmp);

	return 0;
}
