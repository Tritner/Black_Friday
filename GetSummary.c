#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void Error(char* msg) { fprintf(stderr, "Error:%s\n", msg);  exit(1); }

int main(int argc, char* argv[]) {
	int from, rbytes, count = 0, id;
	int i = 0;
	char buff[500];
	char* ptr;
	from = open("/home/braude/Black_Fraidy/camp_partic.txt", O_RDONLY, 0664);
	while (rbytes = read(from, &buff, 500));
	for (i; i < 500; i++) {
		if (buff[i] == '\n') {
			count++;
		}
	}
	int m = 1;
	printf("%d companies take part in the Campaign\n", count);
	ptr = strtok(buff, "\n");
	id = fork();
	if (id == 0) {
		for (m = 1; m <= count; m++) {
			int file_count = 0;
			char dirname[4096];
			DIR* dirp;
			struct dirent* entry;
			sprintf(dirname, "/home/braude/Black_Fraidy/%s_Order", ptr);
			dirp = opendir(dirname);
			if (dirp == NULL) {              // if not dir is open
				Error("open dir"); return -1;
			}

			while ((entry = readdir(dirp)) != NULL) {  //count files
				file_count++;
			}
			printf("%s----%d Orders\n", ptr, file_count - 2); //print
			closedir(dirp);
			ptr = strtok(NULL, "\n");
		}
		close(from);
		execv("/home/braude/Advanced_shell", NULL);
	}
	wait();
	return 0;
}