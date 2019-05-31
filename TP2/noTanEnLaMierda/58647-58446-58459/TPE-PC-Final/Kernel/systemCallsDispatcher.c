#include <time.h>
#include <stdint.h>

#include <keyboardDriver.h>

#include <naiveConsole.h>

#include <videoDriver.h>

#include <graphicsDriver.h>

#include <clock.h>



#include <beeper.h>

#include "include/systemCalls.h"



void pixel(int x, int y);
void printBar(int x,int y);
void get_ticks(unsigned int * ticks);


void systemCallsDispatcher(int sys, int fileDesc, char * buffer, int size, unsigned int * p1, void ** ptr) {

	switch (sys) {
		case 3:
			reads(fileDesc, buffer, size);
			break;
		case 4:
			writes(fileDesc, buffer, size);
			break;
		case 5:
			new_line();
			break;
		case 6:
			get_time();
			break;
		case 7:
			get_date();
			break;
		case 8:
			clear();
			break;

		case 9:
			pixel(fileDesc,size);
			break;


		case 10:
			printBar(fileDesc,size);
			break;

		case 11:
			play_beep();
			break;

		case 12: 
			get_ticks(p1);
			break;

		case 13:
			*ptr = system_malloc(size);
			break;

		case 14:
			system_free(ptr,size);
			break;


	}

	return;
}

void pixel(int x, int y){
	drawBall(x,y);

}

void printBar(int x,int y){
	drawBar(x,y);
}


void get_ticks(unsigned int * ticks){

	
	*ticks = ticks_elapsed();

}
