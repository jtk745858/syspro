#include<sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	int pid, child, status;
	printf("[%d] Start Parent process\n", getpid( ));
	pid = fork();
	if (pid == 0) {
      printf("[%d] Start Child process\n", getpid( ));
      exit(1);
   }
	child = wait(&status);
	printf("[%d] Child process %d exit \n",getpid(), child);
	printf("\t exit code %d\n",status>>8);
}
