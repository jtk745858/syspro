#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("My process Num : [%d]\n",getpid());

	printf("My parent process Num : [%d]\n",getppid());
}


