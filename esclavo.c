#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>


#define BUFFSIZE 256

int main(void){
	//char buff[BUFFSIZE];
	char readBuffer[BUFFSIZE];
	char * prompt = malloc(BUFFSIZE);
	char * md5sum = "md5sum ";
	int flag;

	while(1){

		flag = read(STDIN_FILENO, readBuffer, 256);

		//fprintf(stderr, "%s\n",readBuffer);
		//fprintf(stderr, "%s\n", readBuffer);
		//fprintf(stderr, "%d\n",flag );

		if(flag == 0){
			fprintf(stderr, "%s\n","HOLI" );
			exit(1);
		}

		strcpy(prompt, md5sum);


		strcat(prompt, readBuffer);


		//strcpy(prompt,'\0');

		//fprintf(stderr, "%s\n",prompt );


		//fprintf(STDOUT_FILENO,"%s\n",readBuffer );	

		char buff[BUFFSIZE];
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

		write(STDOUT_FILENO, buff,256);
	}

	exit(1);

}