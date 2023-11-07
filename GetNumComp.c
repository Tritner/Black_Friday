#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include<unistd.h>

int main() {
	int from, rbytes, count = 0;
	int i = 0;
	char buff[500];
	from = open("/home/braude/Black_Fraidy/camp_partic.txt", O_RDONLY);
	while (rbytes = read(from, &buff, 500));
	for (i; i < 500; i++) {
		if (buff[i] == '\n') {
			count++;
		}
	}
	close(from);
	printf("%d companies take part in the Campaign\n", count);
	execv("/home/braude/Advanced_shell", NULL);


}