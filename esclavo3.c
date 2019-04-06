#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFSIZE 256

void calculate_md5(char * filename){
	char * prompt = malloc(BUFFSIZE);
	char * md5sum = "md5sum ";

	strcpy(prompt, md5sum);

	strcat(prompt, filename);


		//strcpy(prompt,'\0');

		//fprintf(stderr, "%s\n",prompt );


		//fprintf(STDOUT_FILENO,"%s\n",readBuffer );	

		//char buff[BUFFSIZE];
		char * buff = malloc(256);
    	FILE *fp;

    	if ((fp = popen(prompt, "r")) == NULL) {
        	//printf("Error opening pipe!\n");
        	//return -1;
        	exit(-1);
    	}

    	while (fgets(buff, BUFFSIZE, fp) != NULL) {
        	// Do whatever you want here...
        	//fprintf(stderr,"OUTPUT: %s", buff);
    	}


    	if(pclose(fp))  {
        	//printf("Command not found or exited with error status\n");
        	//return -1;
        	//exit(-1);
    	}

		write(STDOUT_FILENO, buff,BUFFSIZE);
		free(prompt);
	free(buff);

}

void slave_work(int limit, char* filenames[BUFFSIZE]){
	//char * files_completed[limit];

	int i;
	for(i = 0; i < limit; i++){
		calculate_md5(filenames[i]);
		

	}
}

int main(int argc, const char* argv[]){
	//char buff[BUFFSIZE];
	//char readBuffer[BUFFSIZE];
	char * readBuffer = malloc(256);
	int initial_load = 0;
	if(argv[1] != NULL){
		initial_load = atoi(argv[1]);	
	}
	
	//char files_to_complete[initial_load][BUFFSIZE];
	//fprintf(stderr, "Recibi este initial load = %d\n", initial_load);

	char * files_to_complete[initial_load];
	int i;

	for(i = 0;i<initial_load;i++){
		files_to_complete[i] = malloc(256);
	}

	sem_t semaphore;
	sem_init(&semaphore, 1, 1);
	sem_wait(&semaphore);

	//int i;
	for(i = 0; i < initial_load; i++){
		read(STDIN_FILENO, files_to_complete[i], BUFFSIZE);
		//fprintf(stderr, "ARCHIVO LEIDO: %s HIJO: %d\n",files_to_complete[i],getpid() );

		//fprintf(stderr,"Lei: %s\n", files_to_complete[i]);
	}
	sem_post(&semaphore);

	slave_work(initial_load, files_to_complete);
	char * arr[1];
	arr[0] = malloc(256);

	while(read(STDIN_FILENO,  arr[0], BUFFSIZE)){
		//fprintf(stderr, "%s\n", "llegue oerri");
		sem_wait(&semaphore);
		//memset(files_to_complete[0],0,256);
		//read(STDIN_FILENO, arr[0], BUFFSIZE);
		sem_post(&semaphore);
		//fprintf(stderr, "ARCHIVO LEIDO%s %d\n",arr[0], getpid());

		//calculate_md5(filenames[i]);

		slave_work(1, arr);
		//fprintf(stderr, "%s\n", readBuffer);

		//fprintf(stderr, "%s\n",readBuffer);
		//fprintf(stderr, "%s\n", readBuffer);
		//fprintf(stderr, "%d\n",flag );
	}


	exit(1);

}