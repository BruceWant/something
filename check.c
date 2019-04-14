#include "check_crypto.h"

#define FILE_PATH "E:/vmware/text"

int main()
{
	int num;
	int i;
	config *crypto;

	num = number_crypto(FILE_PATH); /* number of crypto */
	printf("%d\n", num);
	
	crypto = create(num); /* create a uninitialized link list */

	read_file(FILE_PATH, crypto); /* read config file and initial list */

	print(crypto);

	for (i = 0; i < num; i++) {
		delete_dat(crypto, 1);
	}

	getchar();


	return 0;
}
