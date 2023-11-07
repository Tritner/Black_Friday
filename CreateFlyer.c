#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define N 25

void Error(char* msg) { fprintf(stderr, "Error:%s\n", msg);  exit(1); }


int main(int argc, char* argv[]) {

	//define variables
	int i = 0, fd_1, fd_2, k = 1, j = 0, bytes, wbytes;
	char buff[256];
	char downline[N * 2];
	char headline[N];
	char tempname[N];
	char file[2 * N];
	char discount[N];
	char itemName[N];
	int price;
	char dots[N];
	char dirname[2 * N];
	char* tok;
	int checkloop = 1, selection;


	strcpy(headline, "\t\t");
	strcat(headline, argv[1]);
	strcat(headline, " Sale\n");
	strcpy(file, "/home/braude/Black_Fraidy/");
	strcat(file, argv[1]);
	strcat(file, ".txt");
	strcpy(discount, "\t\t");
	strcat(discount, argv[2]);
	strcat(discount, " % off\n");
	fd_2 = open("/home/braude/Black_Fraidy/camp_partic.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
	bytes = strlen(argv[1]);
	wbytes = write(fd_2, argv[1], bytes);
	char* godown = "\n";
	bytes = strlen("\n");
	wbytes = write(fd_2, "\n", bytes);
	if (fd_2 == -1) { Error("couldnt open file"); }
	//open file
	if ((fd_1 = open(file, O_CREAT | O_RDWR, 0664)) == -1) {
		perror("open first file"); return(-1);
	}
	//write the name of the shop at the top
	if (write(fd_1, headline, strlen(headline)) == -1) {

		perror("write"); return(-1);
	}
	if (write(fd_1, discount, strlen(discount)) == -1) {

		perror("write"); return(-1);
	}

	printf("Enter item and item cost:\n");
	do {
		fgets(itemName, 25, stdin);                                         //get to buffer
		if (strcmp(itemName, "Stop\n") == 0) {       //break function if user entered stop
			break;
		}
		//go strtok on temporary name to get the price from the item
		strcpy(tempname, itemName);
		tok = strtok(tempname, " ");
		while (tok != NULL) {
			price = atoi(tok);          //price is always at the end of the string
			tok = strtok(NULL, " ");    //so on the last run it will get the price
		}
		//remove the price from the item
		for (j = 1; j <= price; j = j * 10) {
			itemName[strlen(itemName) - 1] = '\0';
		}
		itemName[strlen(itemName) - 1] = '\0';
		//get the number of dots needed to make it look good
		dots[0] = '\0';
		for (j = 0; j < N - strlen(itemName); j++) {
			strcat(dots, ".");
		}
		//create buffer with all the variables created
		sprintf(buff, "   %s %s %dNIS\n", itemName, dots, price);


		//write from buffer
		if (write(fd_1, buff, strlen(buff)) == -1)
		{
			perror("write"); return(-1);
		}

	} while (strcmp(buff, "Stop\n") != 0);           //stop function if user entered Stop



	printf("What is your choice?\n1.Enjoyed\n2.Shop Now and have fun\n3.Have Fun\n4.Other\n");
	while (checkloop) {

		scanf("%d", &selection);
		switch (selection) {
		case 1:
			strcpy(downline, "Enjoyed\n");
			checkloop = 0;
			break;
		case 2:
			strcpy(downline, "Shop Now and have fun\n");
			checkloop = 0;
			break;
		case 3:
			strcpy(downline, "Have fun\n");
			checkloop = 0;
			break;
		case 4:
			printf("Enter other sentence please: \n");
			fgetc(stdin);
			fgets(downline, N * 2, stdin);
			checkloop = 0;
			break;
		default:
			printf("select again please\n");
		}
	}
	strcpy(buff, "\t\t");
	strcat(buff, downline);
	if (write(fd_1, buff, strlen(buff)) == -1)         //write from buffer
	{
		perror("write"); return(-1);
	}
	close(fd_1);
	strcpy(dirname, "/home/braude/Black_Fraidy/");
	strcat(dirname, argv[1]);
	strcat(dirname, "_Order");           //create name for dir
	if (mkdir(dirname, 0777) == -1) {        //create dir
		perror("open dir");
	}
	printf("Successfully created // %s created , %s dir created.\n", file, dirname);

	execv("/home/braude/Advanced_shell", NULL);

	return 0;
}