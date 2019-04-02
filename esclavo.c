#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFSIZE 256

char * calculate_md5(char * filename){
	return  "que haces campeon\n";
}

void slave_work(int limit, char filenames[][BUFFSIZE]){
	char * files_completed[limit];

	for(int i = 0; i < limit; i++){
		files_completed[i] = calculate_md5(filenames[i]);
		write(STDOUT_FILENO, files_completed[i], BUFFSIZE);

	}
}

int main(int argc, char * argv[]){
	fprintf(stderr, "Cree un esclavo\n");
	int initial_load = atoi(argv[1]);
	char files_to_complete[initial_load][BUFFSIZE];
	fprintf(stderr, "Recibi este initial load = %d\n", initial_load);
	sem_t semaphore;
	sem_init(&semaphore, 1, 1);
	sem_wait(&semaphore);

	for(int i = 0; i < initial_load; i++){
		read(STDIN_FILENO, files_to_complete[i], BUFFSIZE);
		fprintf(stderr,"Lei: %s\n", files_to_complete[i]);
	}
	sem_post(&semaphore);

	slave_work(initial_load, files_to_complete);
	int j = 0;

	while(j < 1){

		sem_wait(&semaphore);
		read(STDIN_FILENO, files_to_complete[0], BUFFSIZE);
		sem_post(&semaphore);
		j++;
		slave_work(1, files_to_complete);
	}

	exit(1);
}



