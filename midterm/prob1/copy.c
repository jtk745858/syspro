#include <stdio.h>

int main(int argc, char *argv[])
{
	char c;
	FILE *fp1, *fp2;

	if(argc != 4)
	{
		fprintf(stderr,"How to use: %s Option File1 File2\n", argv[0]);
		return 1;
	}
	
	fp1 = fopen(argv[2],"r");
	
	if(fp1 == NULL)
	{
		fprintf(stderr,"File %s Open Error\n",argv[2]);
		return 2;
	}
	fp2 = fopen(argv[3],"w");
	if(*argv[1] == '0')
	{
		while((c=fgetc(fp1)) != EOF)
		{
			fputc(c,fp2);
		}
	}
	else if(*argv[1] == '1')
	{
		while((c=fgetc(fp1))!= EOF)
		{
			if(c >64 && c < 91)
			{
				fputc(c+32,fp2);
			}
			else
			{
				fputc(c,fp2);
			}
		}

	}
	else if(*argv[1] == '2')
	{
		while((c=fgetc(fp1)) != EOF)
		{
			if(c > 96 && c < 123)
			{	
				fputc(c-32,fp2);
			}
			else
			{
				fputc(c,fp2);
			}
		}

	}
	else 
		fprintf(stderr,"%s: wrong value",argv[1]);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
