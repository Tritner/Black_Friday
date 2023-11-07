#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <ftw.h>
#include <unistd.h>

void Endmessege(char* msg) { fprintf(stderr, "%s\n", msg);  exit(1); }

int main(int argc, char* argv[]) {

	int id;
	id = fork();
	if (id == 0) {
		execl("/bin/rm", "/bin/rm", "-rf", "Black_Fraidy", 0);
		printf("execl failed");
	}
	if (id != 0) {
		Endmessege("GoodBye..\n");
	}
}