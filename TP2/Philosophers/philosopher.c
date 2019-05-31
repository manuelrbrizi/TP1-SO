#include <time.h>
#include "include/shell.h"
#include "include/stdInOut.h"
#include "include/stringUtilities.h"
#include "include/dateTime.h"
#include "include/memoryLib.h"

enum status{Thinking,Hungry,Eating};

void philosopher(int id){
	enum status state;
	while(1){
		state[id]=Thinking;
		printCharAt("T",50+((id-1)/2)*50,200*((id%2)+1));
		sleep(rand%3);
		state[id]=Hungry;
		printCharAt("H",50+((id-1)/2)*50,200*((id%2)+1));
		if(id%2==0){
			waitRight(id);
			waitLeft(id);
			state[id]=Eating;
			printCharAt("E",50+((id-1)/2)*50,200*((id%2)+1));
			sleep(rand%3);
		}
		if(id%2==1){
			waitLeft(id);
			waitRight(id);
			state[id]=Eating;
			printCharAt("E",50+((id-1)/2)*50,200*((id%2)+1));
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
	int pids[10];
	int totalP=1;
	enum status state[20];
	while(totalP<4){
		sem_create(totalP*-1,1);
		pids[totalP]=createPhilosopher(totalP);

		totalP++;
	}
	char command;
	while(1){
		command=get_char();
		if(command==t)
			return 1;
		if(command=a){
			if(totalP<=20){
				sem_create(totalP);
				pids[totalP]=createPhilosopher(totalP);
				totalP++;
			}
			else {
				print_string("only 20 philosophers at the same time");
			}
		}
		if(command=d){
			if(totalP<=2){
				print_string("there needs to be at least 2 philosophers");
			}
			else{
				totalP--;
				deletePhilosopher(pids[totalP]);
			}
		}

	}

} 

int createPhilosopher(int id){
	Process_info_t* process;
	process->p1=id;
	process->p2;
	process->p3;
	process->ground='b';
	process->tickets=100;
	void (*ptr_funct)(int)=philosopher;
	process-entryPoint=ptr_funct;
	process->fd1=0;
	process->fd2=1;
	char buffy[10];
	uintToBase(id,buffy,10);
	process->process_name="philosopher "+buffy;
	return execute(process);
}

void deletePhilosopher(int id){
	kill(id);
}