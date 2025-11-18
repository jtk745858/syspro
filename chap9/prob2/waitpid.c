#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	 int pid1, pid2, child, status;

     printf("[%d] start parent process\n", getpid());
     pid1 = fork();
     if (pid1 == 0) {
		printf("[%d] start child process[1] \n", getpid());
		sleep(1);
		printf("[%d] exit child process \n", getpid());
	 	exit(1);
	}
	 pid2 = fork();
	 if(pid2 == 0) {
		 printf("[%d] start child process #2 \n",getpid());
		 sleep(2);
		 printf("[%d] exit child process #2 \n", getpid());
		 exit(2);
	}
	child = waitpid(pid1,&status,0);
	printf("[%d] exit child process #1 %d\n", getpid( ), child);
	printf("\t exit code %d\n",status>>8);
	
}
