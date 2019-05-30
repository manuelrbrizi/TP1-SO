#include <time.h>
#include "include/shell.h"
#include "include/stdInOut.h"
#include "include/stringUtilities.h"
#include "include/dateTime.h"
#include "include/memoryLib.h"

enum status{Thinking,Hungry,Eating};

void philosopher(int id){
	while(1){
		enum status state=Thinking;
		sleep(rand%3);
		status=Hungry;
		if(id%2==0){
			waitRight(id);
			waitLeft(id);
			status=Eating;
			sleep(rand%3);
		}
		if(id%2==1){
			waitLeft(id);
			waitRight(id);
			status=Eating;
			sleep(rand%3);
		}
		putDownLeft(id);
		putDownRight(id);

	}
}

void waitRight(int id){
	sem_wait((id+1)%totalP)
}

void waitRight(int id){
	sem_wait((id-1)%totalP)
}

void putDownLeft(int id){
	sem_post((id+1)%totalP)
}

void putDownRight(int id){
	sem_post((id-1)%totalP)
}

int main( int argc, char *argv[ ], char *envp[ ]){
	int i=0;
	while(i<3){
		sem_create(i,1);
		createPhilosopher(i);

		i++;
	}
	
} 