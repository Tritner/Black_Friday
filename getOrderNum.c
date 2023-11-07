#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
	int file_count = 0;
	char dirname[4096];
	DIR* dirp;
	struct dirent* entry;
	sprintf(dirname, "/home/braude/Black_Fraidy/%s_Order", argv[1]);
	dirp = opendir(dirname);
	if (dirp == NULL) {              // if not dir is open
		printf("Company not found\n");
		execv("/home/braude/Advanced_shell", NULL);
		exit(1);
	}

	while ((entry = readdir(dirp)) != NULL) {  //count files
		file_count++;
	}
	printf("%s----%d Orders\n", argv[1], file_count - 2); //print
	closedir(dirp);
	execv("/home/braude/Advanced_shell", NULL);
}