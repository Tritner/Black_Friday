#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

void Error(char* msg) { fprintf(stderr, "Error:%s\n", msg);  exit(1); }

int main(int argc, char* argv[]) {
	int id;
	char path[100] = "/home/braude/Black_Fraidy/";
	strcat(path, argv[1]);
	id = fork();
	if (id == 0) {
		execl("/bin/cat", "cat", path, 0);
		printf("execl failed");
	}
	wait();
	execv("/home/braude/Advanced_shell", NULL);

}