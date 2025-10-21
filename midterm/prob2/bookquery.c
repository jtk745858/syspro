#include <stdio.h>
#include <stdlib.h>
#include "bookinfo.h"

int main(int argc,char *argv[]){
	
	struct bookinfo rec;
	FILE *fp;
	if(argc != 2){
		fprintf(stderr, "How to use: %s Option\n",argv[0]);
		return 1;
	}

	fp = fopen("./database.txt","r");

	if(*argv[1] == '0')
	{
		printf("%-4s %-12s %-10s %-6s %-14s %s\n","id","bookname","author","year","numofborrow","borrow");
		while(fscanf(fp,"%d %s %s %d %d %s",&rec.num,rec.name,rec.writer,&rec.year,&rec.rent,rec.flag) ==6)
			printf("%5d %11s %9s %5d %13d %s\n",rec.num,rec.name,rec.writer,rec.year,rec.rent,rec.flag);
	}
	else if(*argv[1] == '1')
	{	
		printf("%-4s %-12s %-10s %-6s %-14s %s\n","id","bookname","author","year","numofborrow","borrow");
		while(fscanf(fp,"%d %s %s %d %d %s",&rec.num,rec.name,rec.writer,&rec.year,&rec.rent,rec.flag) ==6)
		{
			if(rec.flag == "True")
			{
				printf("%5d %11s %9s %5d %13d %s\n",rec.num,rec.name,rec.writer,rec.year,rec.rent,rec.flag);
			}

		}
	}
	fclose(fp);
	return 0;
}

