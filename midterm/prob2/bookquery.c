#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookinfo.h"

void printInfo(struct bookinfo rec){
	printf("%d\t%-20s\t%-15s\t%d\t%d\t\t%s\n",
           rec.id,
           rec.name,
           rec.writer,
           rec.year,
           rec.numBorrow,
           rec.canBorrow ? "True" : "False");
}

int main(int argc, char *argv[])  
{
	if(argc != 1){
		fprintf(stderr,"How to use: %s",argv[0]);
		return 1;
	}
	struct bookinfo rec;
	int option;

	printf("0 : list of all books, 1 : list of avaliable books ) ");
	scanf("%d",&option);

	if(option != 0 && option != 1)
	{
		printf("Error : Input 0 or 1");
		return 1;
	}

	FILE *fp = fopen("db.dat","rb");
	if (fp == NULL) {
		printf("Error : Can not open file");
		return 1;
		}
	printf("id\tbookname\tauthor\t\tyear\tnumofborrow\tborrow\n");
	while (fread(&rec, sizeof(struct bookinfo), 1,fp) == 1) {
		if(option == 0) {
			printInfo(rec);
		}
		else if (option == 1)
		{
			if (rec.canBorrow == 1) {
				printInfo(rec);
			}
		}
	}
	fclose(fp);
	return 0;
}


