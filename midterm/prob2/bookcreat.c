#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bookinfo.h"
int main(int argc,char *argv[])
{
	struct bookinfo rec[4] = {
		{1,"1984","George",2020,7,0},
		{2,"Luster","Raven",2020,3,1},
		{3,"Hamnet","Maggie",2020,0,0},
		{4,"theWish","Nocholas",2021,2,1}
	};
	FILE *fp = fopen("db.dat","wb");
	if(argc != 1) {
		fprintf(stderr,"How to use: %s",argv[0]);
	}
	if(fp == NULL){
		printf("Can't open db.dat File");
		return 1;
		}
	
	int write_cnt = fwrite(rec, sizeof(struct bookinfo),4,fp);

	fclose(fp);

	printf("Success to generate db.dat file\n");
	return 0;
}
