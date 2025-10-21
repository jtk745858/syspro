#include <stdio.h>
#include <stdlib.h>
#include "bookinfo.h"
int main(int argc,char *argv[])
{
	struct bookinfo rec;
	FILE *fp;
	if(argc != 1){
		fprintf(stderr, "How to use: %s",argv[0]);
		exit(1);
	}
	fp = fopen("./database.txt","w");

	printf("%-4s %-12s %-10s %-6s %-14s %s\n","id","bookname","author","year","numofborrow","borrow");

	while(scanf("%d %s %s %d %d %s",&rec.num,rec.name,rec.writer,&rec.year,&rec.rent,rec.flag) == 6)
		fprintf(fp,"%d %s %s %d %d %s ",rec.num,rec.name,rec.writer,rec.year,rec.rent,rec.flag);
	
	fclose(fp);
	return 0;
}
