#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>



int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main( int argc, const char* argv[] ){
	
	int sent = 1;
	int recieved = 0;


	/*
	for(int i = 0; i<argc ; i++){
		if(is_regular_file(argv[i])){
			printf("File Name:\t\t" );
		}
		else{
			printf("Directory Name:\t\t" );
		}
		printf("%s\n",argv[i]);

	}*/
	
	char buffer[256];


	int filePipe[2],hashPipe[2];

	pipe(filePipe);
	pipe(hashPipe);


	int child_pid;


	if((child_pid=fork()) == 0){
		close(0);
		dup(filePipe[0]);
		close(filePipe[0]);
		close(filePipe[1]);

		close(1);
		dup(hashPipe[1]);
		close(hashPipe[0]);
		close(hashPipe[1]);

		execl("esclavo", "esclavo", (char *) NULL);
	}

	else{
		close(hashPipe[1]);
		close(filePipe[0]);
		

		while(sent < argc){
			printf("%s\n",argv[sent] );
			write(filePipe[1],argv[sent],256);
			sent++;
		}
		//char * end = "TERMINE\0";

		//write(filePipe[1],end ,256);
		//write(filePipe[1], "FINDELINPUT\0",256);
		//close(filePipe[1]);


		


		while(recieved<sent-1){
			read(hashPipe[0], buffer, 256);
			printf("%s\n",buffer );
			recieved++;

		}

		printf("%s\n", "SALGO");
		
		return 1;

		//waitpid(-1, NULL, 0);


		//kill(child_pid, SIGKILL);
	}

	//write(filePipe[1],"HOLA\0",5);
}