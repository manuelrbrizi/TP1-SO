#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFSIZE 256
#define CHILDQTY 3

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int get_initial_load(int args){
	return 5;
}
/*
void create_slave(int filePipe[], int hashPipe[], int argc){
	//sobre stdin
	printf("Estoy por crear un esclavo1!\n");
	close(0);
	dup(filePipe[0]);
	close(filePipe[0]);
	close(filePipe[1]);
	printf("Estoy por crear un esclavo2!\n");
	//sobre stdout
	close(1);
	dup(hashPipe[1]);
	close(hashPipe[0]);
	close(hashPipe[1]);
	execl("esclavo", "esclavo", get_initial_load(argc));
}*/

int main(int argc, const char* argv[] ){
	//printf("Recibi esta cantidad de argumentos: %d\n", argc);
	//char buffer[BUFFSIZE];
	char * buffer = malloc(256);
	int filePipe[2],hashPipe[2], requestPipe[2];
	pipe(filePipe);
	pipe(hashPipe);
	pipe(requestPipe);



	int pid;

	int i;
	for(i = 0; i < CHILDQTY; i++){
		if((pid=fork()) == 0){
			//create_slave(filePipe, hashPipe, argc);
			close(0);
			dup(filePipe[0]);
			close(filePipe[0]);
			close(filePipe[1]);
		
			close(1);
			dup(hashPipe[1]);
			close(hashPipe[0]);
			close(hashPipe[1]);

			char * str = malloc(BUFFSIZE);
			snprintf(str, BUFFSIZE, "%d", get_initial_load(argc));
			execl("esclavo3", "esclavo3", str, (char *)NULL);
		}
	}
	
	//aca tengo que mandarle el nombre de los archivos


	if(pid != 0) {	

		char * file_name = malloc(BUFFSIZE);

		//fprintf(stderr, "Escribi re piola\n");
		close(hashPipe[1]);
		close(filePipe[0]);

		int i;
		for(i = 1;i<argc;i++){

			strcpy(file_name,argv[i]);
			write(filePipe[1],file_name,BUFFSIZE);
		}

		close(filePipe[1]);
			int recieved = 0;
	
	while(recieved < argc-1){
		read(hashPipe[0], buffer, BUFFSIZE);
		printf("%s",buffer);
		recieved ++;
	}


	}

	


	return 1;
	
}