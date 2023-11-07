#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define N 25

int main(int argc, char* argv[]) {
	int num, num_orders, i, fd_1, fd_2, rbytes, price;
	double sum = 0;
	char path[256];
	char buff[1024];
	char rbuff[256];
	char companyname[N];
	char costumername[N];
	char filename[N * 2];
	char itemname[N];
	char tempname[N];
	char origitem[N];
	char* tok;
	char* ptr;
	double Discount;
	char discount[N];
	int id;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);



	strcpy(costumername, argv[2]);
	strcpy(companyname, argv[1]);
	sprintf(path, "/home/braude/Black_Fraidy/%s_Order/%s.txt", companyname, costumername);
	sprintf(filename, "/home/braude/Black_Fraidy/%s.txt", companyname);
	//open read file 
	if ((fd_2 = open(filename, O_RDONLY)) == -1)
	{
		printf("Company Not Found!\n");
		execv("/home/braude/Advanced_shell", NULL);
	}
	id = fork();
	if (id == 0) {
		if (execlp("cat", "cat", filename, NULL) == -1) {
			perror("execlp");
			exit(1);
		}
	}
	wait();
	rbytes = read(fd_2, buff, 1);
	buff[1] = '\0';
	while (rbytes > 0 && buff[0] != '%') {
		if (buff[0] >= '0' && buff[0] <= '9')
		{
			discount[i] = buff[0];
			i++;

		}
		rbytes = read(fd_2, buff, 1);
		buff[1] = '\0';

	}
	discount[i] = '\0';
	Discount = atoi(discount);
	//print on top of order
	sprintf(buff, "\n%s Order\n\n", companyname);

	printf("Insert your order (STOP to finish);\n");

	//loop to get the order inputs

	while (1) {
		lseek(fd_2, 0, SEEK_SET);

		price = 0;
		fgets(itemname, 25, stdin);                                     //get item name
		itemname[strlen(itemname) - 1] = '\0';

		if (strcmp(itemname, "STOP\0") == 0) {             //break function if user entered Finish
			break;
		}
		else {


			//go strtok on temporary name to get the num of orders from the item name
			strcpy(tempname, itemname);
			strcpy(origitem, itemname);
			strcat(origitem, "\n");
			tok = strtok(tempname, " ");
			while (tok != NULL) {
				num_orders = atoi(tok);          //num of orders is always at the end of the string
				tok = strtok(NULL, " ");    //so on the last run it will get the price

			}

			//remove the num from the item name
			for (i = 1; i <= num_orders; i = i * 10) {
				itemname[strlen(itemname) - 1] = '\0';
			}
			//read from flyer
			if ((rbytes = read(fd_2, rbuff, 256)) == -1)
			{
				perror("read"); return(-1);
			}

			// go for a loop and check if the word is in the rbuffer
			while (rbytes > 0) {
				ptr = NULL;
				ptr = strstr(rbuff, itemname);             // find the item name
				if (ptr != NULL && strcmp(ptr, origitem) != 0) {        //if found get price 
					ptr += 27;
					price = (atoi(ptr));
					if (price != 0) {              //check that buff isnt cut without price
						break;
					}
					else {

						lseek(fd_2, -50, SEEK_CUR);               //go back that we wont miss an order that we "cut" in two  
					}
				}
				if ((rbytes = read(fd_2, rbuff, 256)) == -1) //keep reading if not found
				{
					perror("read 2"); return(-1);
				}
			}
		}

		if (price == 0) {
			printf("item Not Found!\n");  //if cant find the item
		}
		else {
			sum += (num_orders * price) * ((100 - Discount) / 100);   //calculate total amount
			strcat(buff, origitem);          //add item to buffer
			strcat(buff, "\n");
		}



	}
	sprintf(tempname, "\nTotal Price: %.2fNIS", sum); //add total amount to buff
	strcat(buff, tempname);
	printf("\n%s  (Confirm to approve/else cancel)\n", tempname);
	fgets(tempname, N, stdin);

	if (strcmp(tempname, "Confirm\n") == 0) {
		//open write file
		if ((fd_1 = open(path, O_CREAT | O_RDWR, 0664)) == -1) {
			perror("open order file"); return(-1);
		}
		//write from buffer
		if (write(fd_1, buff, strlen(buff)) == -1)
		{
			perror("write"); return(-1);
		}
		sprintf(buff, "\n\n%d-%02d-%02d %02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min); //get date and time
		if (write(fd_1, buff, strlen(buff)) == -1) //print to the order
		{
			perror("write"); return(-1);
		}
		chmod(path, 0444);
		printf("Order created! // %s.txt Created in %s_Order Dir with Read Mode\n", costumername, companyname);


	}


	close(fd_1);
	close(fd_2);
	execv("/home/braude/Advanced_shell", NULL);


	return 0;
}
