#include <stdio.h>
#include "copy.h"
#include <string.h>

#define STRING 5

int main(void) {
	char str[STRING][MAXLINE];
	char temp[MAXLINE];
	int i,j;
	i = 0;
	while (i < STRING) {
		fgets(str[i],MAXLINE,stdin);

		str[i][strcspn(str[i],"\n")] = '\0';
		i++;
	}
	i = 0;
	while (i < STRING-1) {
		j = i + 1;
		while(j < STRING) {
			if(strlen(str[i]) < strlen(str[j])) {
				copy(str[i],temp);
				copy(str[j], str[i]);
				copy(temp, str[j]);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < STRING) {
		printf("%s\n", str[i]);
		i++;
	}
	return 0;
}


