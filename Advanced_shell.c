#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include<unistd.h>

void Error(char* msg) { fprintf(stderr, "Error:%s\n", msg);  exit(1); }

int main() {
	int file;
	int s = mkdir("Black_Fraidy", 0700);	//open dir black friday
	file = open("/home/braude/Black_Fraidy/camp_partic.txt", O_WRONLY | O_CREAT, 0664);
	char bin[256] = "/bin/";
	int id;
	char buffer[251];//create buffer get inputs
	char* buffer0[4];
	printf("AdvShell>");
	while (fgets(buffer, 251, stdin)) {		//while loop execv C programs while fgets!="Stop"
		if (0 == strcmp(buffer, "\n")) {
			execv("/home/braude/Advanced_shell", NULL);
			printf("execv faild strcmp = %d", strcmp(buffer0[0], "\n"));
		}
		buffer[strcspn(buffer, "\n")] = 0;	//break the parameters 
		buffer0[0] = strtok(buffer, " ");
		buffer0[1] = strtok(NULL, " ");
		buffer0[2] = strtok(NULL, " ");
		buffer0[3] = strtok(NULL, " ");
		if (buffer0[3] != NULL) {
			if (id = fork() == 0) {			//check how much parameters we got
				strcat(bin, buffer0[0]);
				execl(bin, buffer0[0], buffer0[1], buffer0[2], buffer0[3], 0);
				Error("Not supported");
			}
		}
		else
			if (buffer0[2] != NULL) {
				if (0 == strcmp(buffer0[0], "CreateFlyer")) {
					execv("/home/braude/CreateFlyer", buffer0);
					printf("execv faild strcmp = %d", strcmp(buffer0[0], "exit"));

				}
				if (0 == strcmp(buffer0[0], "MakeOrder")) {
					execv("/home/braude/MakeOrder", buffer0);
					printf("execv faild strcmp = %d", strcmp(buffer0[0], "exit"));

				}
				if (id = fork() == 0) {
					strcat(bin, buffer0[0]);
					execl(bin, bin, buffer0[1], buffer0[2], 0);
					Error("Not supported");
					wait();
					printf("\nAdvShell>");
				}
			}
			else
				if (buffer0[1] != NULL) {
					if (0 == strcmp(buffer0[0], "GetOrderNum")) {
						execv("/home/braude/GetOrderNum", buffer0);
						printf("execv faild strcmp = %d", strcmp(buffer0[0], "GetOrderNum"));

					}
					if (0 == strcmp(buffer0[0], "GetFlyer")) {
						execv("/home/braude/GetFlyer", buffer0);
						printf("execv faild strcmp = %d", strcmp(buffer0[0], "exit"));

					}
					if (id = fork() == 0) {
						strcat(bin, buffer0[0]);
						execl(bin, buffer0[0], buffer0[1], 0);
						Error("Not supported");
					}
				}
				else {
					if (0 == strcmp(buffer0[0], "GetSummary")) {
						execv("/home/braude/GetSummary", NULL);
						printf("execv faild strcmp = %d", strcmp(buffer0[0], "GetSummary"));
					}

					if (0 == strcmp(buffer0[0], "exit")) {
						execv("/home/braude/exit", NULL);
						printf("execv faild strcmp = %d", strcmp(buffer0[0], "exit"));
					}
					if (0 == strcmp(buffer0[0], "GetNumComp")) {
						execv("/home/braude/GetNumComp", NULL);
						printf("execv faild strcmp = %d", strcmp(buffer0[0], "GetNumComp"));
					}

					if (id = fork() == 0) {
						strcat(bin, buffer0[0]);
						execl(bin, buffer0[0], 0);
						Error("Not supported");
					}
				}

		wait();
		printf("// Black_Friday dir created, camp_partic.txt created\n");
		printf("\nAdvShell>");
		close(file);
	}
	return 0;
}