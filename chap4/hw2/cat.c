#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void processFile(FILE *stream,int show_lineNumber, int *lineNumber) {
	int c;
	int startLine = 1;
	while ((c = fgetc(stream)) != EOF) {
		if(show_lineNumber && startLine) {
			printf("%2d\t",(*lineNumber)++);
			startLine = 0;
		}
		putchar(c);
		if(c=='\n') {
			startLine = 1;
		}
	}
}
int main(int argc, char *argv[]) {
    int show_lineNum = 0;
    int line_number = 1;
    int file_count = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            show_lineNum = 1;
        } else {
            file_count++;
        }
    }
    if (file_count == 0) {
        processFile(stdin, show_lineNum, &line_number);
    } else {

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-n") == 0) {
                continue;
            }



            FILE *fp = fopen(argv[i], "r");


            if (fp == NULL) {
                fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
                continue;
            }

            processFile(fp, show_lineNum, &line_number);
            fclose(fp);
        }
    }

    return 0;
}
