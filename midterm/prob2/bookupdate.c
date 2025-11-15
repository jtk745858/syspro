#include <stdio.h>
#include <stdlib.h>
#include "bookinfo.h"

void printInfo(struct bookinfo rec) {
	printf("%d\t%-15s\t%-15s\t%d\t%d\t\t%s\n",
           rec.id,
           rec.name,
           rec.writer,
           rec.year,
           rec.numBorrow,
           rec.canBorrow ? "True" : "False");
}

int main() {
	int option;
	int target;
	struct bookinfo rec;
	int found = 0;

	printf("0 bookID: borrow book, 1 bookID: return book ) ");
	
	if (scanf("%d %d", &option, &target) != 2) {
		printf("Error : Wrong input. (ex: 0 3)\n");
		return 1;
	}

	FILE *fp = fopen("db.dat","r+b");
	if(fp == NULL) {
		printf("Error : Can not open file.");
		return 1;
	}

	while (fread(&rec,sizeof(struct bookinfo), 1, fp) == 1) {
		if (rec.id == target) {
			found = 1;
			
			if (option == 0) {
				if (rec.canBorrow == 1) {
					printf("You can not borrow below book since it has been booked.\n");
				}
				else {
					rec.canBorrow = 1;
					rec.numBorrow++;

					fseek(fp, -sizeof(struct bookinfo), SEEK_CUR);
					fwrite(&rec, sizeof(struct bookinfo), 1, fp);

					printf("You've got bellow book...\n");
					}
			}
			else if (option == 1) {
				if (rec.canBorrow == 0) {
					printf("This book is already returned\n");
				}

				else  {
					rec.canBorrow = 0;

					fseek(fp, -sizeof(struct bookinfo), SEEK_CUR);
					fwrite(&rec, sizeof(struct bookinfo),1, fp);

					printf("You've returned bellow book...\n");
					
					}
			}
			else 
			{
				printf("Wrong input : You can input 0 or 1).\n");
				break;
			}

			printf("id\tbookname\tauthor\t\tyear\tnumofborrow\tborrow\n");
			printInfo(rec);

			break;
		}
	}
	if(!found)
	{
		printf("Can not found bookID : %d\n",target);
	}

	fclose(fp);
	return 0;
}

				



