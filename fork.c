#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <unistd.h>
#include <syslog.h>


#define BUFFER 255

void mylog(char *str);

void command(const char *cmd)
{
	FILE *fp;
	char *ret;
	char buf[BUFFER]; 

	if ((fp = popen(cmd, "r")) == NULL) {
		printf("popen filed\n");
		exit(EXIT_FAILURE);
	}

	while ((ret = fgets(buf, sizeof(buf), fp)) != NULL) {
		//printf("%s\n", buf);
		mylog(buf);
	}

	if (pclose(fp) == -1) {
		printf("pclose failed\n");
	}
}



void mylog(char *str)
{
	openlog("info", LOG_PID, LOG_LOCAL2);
	syslog(LOG_INFO, "%s", str);
	//closelog();
}


int utochar(unsigned int num, char *arr)
{
	unsigned int quotient = 0;

	quotient = num / 10;
	if (quotient > 0) {
		utochar(quotient, arr);
	}

	if (quotient == 0)
		return 0;

	*arr++ = (char)(num % 10);
	return 0;
}





int main()
{
	pid_t pid;
	int i;





	for (i = 0; i < 16; i++) {
		if ((pid = fork()) < 0)
			printf("fork file");
		if (pid == 0)
			break;
	}


	if (pid == 0) {
		//char str_pid[11] = {0};
		pid_t child_pid = getpid();

		int len = snprintf(NULL, 0, "%d", child_pid);
		char *str_pid= malloc(len + 1);

		snprintf(str_pid, len + 1, "%d", child_pid);

		//printf("pid: %d, str_pid: %s\n", child_pid, str_pid);

		char cmd1[255] = "cdsk create_vol --passphrase \
				    Zzz1234 --file_size 5M \
				    --file_name /home/tao/crypto/d";
		char cmd2[255] = "cdsk open_vol --passphrase \
				    Zzz1234 --mount_path \
				    /home/tao/crypto/mount/d";
		char cmd3[255] = "cdsk close_vol --file_name \
				    /home/tao/crypto/d";
		char cmd4[255] = "cdsk delete_vol --file_name \
				    /home/tao/crypto/d";

		/* create_vol command */
		strncat(cmd1, str_pid, strlen(str_pid) + 1);
		
		/* open_vol command */
		strncat(cmd2, str_pid, strlen(str_pid) + 1);
		strncat(cmd2, " --file_name /home/tao/crypto/d",
			strlen(" --file_name /home/tao/crypto/d") + 1);
		strncat(cmd2, str_pid, strlen(str_pid) + 1);

		/* close_vol command */
		strncat(cmd3, str_pid, strlen(str_pid) + 1);
		strncat(cmd3, " --mount_path /home/tao/crypto/mount/d", 
			strlen(" --mount_path /home/tao/crypto/mount/d")+1);
		strncat(cmd3, str_pid, strlen(str_pid) + 1);

		/* delete_vol command */
		strncat(cmd4, str_pid, strlen(str_pid) + 1);


		//mylog(cmd1);
		command(cmd1);

		//mylog(cmd2);
		command(cmd2);
		sleep(1);
		
		//mylog(cmd3);
		command(cmd3);

		//mylog(cmd4);
		command(cmd4);

		//printf("%d\n", child_pid);

		free(str_pid);

	}

	//exit(EXIT_SUCCESS);
	


	exit(EXIT_SUCCESS);
}
