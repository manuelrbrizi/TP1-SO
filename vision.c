#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
// #include <sys/mmap.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
	int pid;
	if( argc>1){
		pid=atoi(argv[1]);
	}
	else pid=9999;


	char* sharedmem=shmat(pid,(void*)0,0);
	char c= sharedmem[0];
	int i=0;
	while(1){
		if(c==0){
			i=0;
			c=sharedmem[i];
			system("clear");
		}
		else if(c==EOF){
			break;
		}
		else {printf("%c",c);
		i++;
		c=sharedmem[i];
		}	

	}	





	return 0;
}