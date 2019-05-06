#include <time.h>
#include "include/shell.h"
#include "include/stdInOut.h"
#include "include/stringUtilities.h"
#include "include/dateTime.h"
#include "include/memoryLib.h"


#define MEM_ACCES 10
#define EMPTYCOUNT 11 
#define FILLCOUNT 12
#define BUFFERSIZE 1024

struct area
{
	void* initial;
	int current_reading;
	int current_writing;
};

int main(void){

	sem_create(MEM_ACCES,1);
	sem_create(EMPTYCOUNT,0);
	sem_create(FILLCOUNT,BUFFERSIZE);
	struct area currentarea;
	currentarea.initial=malloc(BUFFERSIZE);
	currentarea.current_writing=0;
	currentarea.current_reading=0;

	return 0;
}

void producer(struct area currentarea){
	s
	while(1){
		int ticks=ticks_elapsed()%10000;
		char number[4];
		number[0]=ticks/1000;
		number[1]=ticks/100-number[0]*10;
		number[2]=ticks/10-number[0]*100-number[1]*10;
		number[3]=ticks-number[0]*1000-number[1]*100-number[2]*10;
		number[4]='\0'
		sem_wait(EMPTYCOUNT);
		sem_wait(MEM_ACCES);
		for(i=0,i<5,i++){
			currentarea.initial[currentarea.current_writing+i]=number[i];
			currentarea.current_writing=(currentarea.current_writing+4)%1024
		}
		sem_post(MEM_ACCES);
		sem_post(FILLCOUNT);

	}
}

void consumer(struct area currentarea){
	while(1){
		char number;
		sem_wait(FILLCOUNT);
		sem_wait(MEM_ACCES);
		for(i=0,i<5,i++){
			number[i]=currentarea.initial[currentarea.current_reading+i];
			currentarea.current_reading=(currentarea.current_reding+4)%1024
		}
		sem_post(MEM_ACCES);
		sem_post(EMPTYCOUNT);
		print_string(elem);

	}

}