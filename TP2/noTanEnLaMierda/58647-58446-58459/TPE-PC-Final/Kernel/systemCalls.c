#include "include/keyboardDriver.h"
#include "include/videoDriver.h"

#include "include/graphicsDriver.h"

#include "include/clock.h"

#include "include/memoryManager.h"

void reads(int fileDesc, char * buffer, int size){
	read_buffer(buffer, size);
}

void writes(int fileDesc, char * buffer, int size){
	drawString(buffer,size);
}

void new_line(){
	newLine();
}


void get_time(){
	time();
}

void get_date(){
	date();
}

// void * system_malloc(int size,void ** ptr){
// 	malloc(size,ptr);
// }


void * system_malloc(int size){
	return malloc(size);
}

void system_free(void *ptr, int size){
	free(ptr, size);
}