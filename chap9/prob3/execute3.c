#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int child, pid, status;
  	pid = fork();

	if(pid == 0) {
		execvp(argv[1],&argv[1]);
	}
	else {
		child = wait(&status);
		printf("[%d] exit child process %d \n",getpid(),pid);
		printf("\texit code %d \n",status>>8);
	}
}
