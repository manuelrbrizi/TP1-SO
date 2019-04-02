#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
	char readBuffer[80] = {'\0'};

	while(1){
		read(STDIN_FILENO, readBuffer, 80);

		//fprintf(stderr, "%s",readBuffer);
		//readBuffer[0]='\0';

		//fprintf(stderr, "HOLA\n" );	
		printf("%s\n",readBuffer );	
		write(STDOUT_FILENO, readBuffer,80);


		//system("md5sum aplicacion2.c");
	}

	exit(1);

}