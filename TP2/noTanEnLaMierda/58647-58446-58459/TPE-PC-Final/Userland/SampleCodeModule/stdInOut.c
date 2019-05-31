#include "include/stdInOut.h"

#include "include/stringUtilities.h"

extern void _int80(int sys, int fileDesc, char* buffer, int size,unsigned int * p1,void ** ptr);

void put_char(char c) {
	_int80(4,1,&c,1,0,0);
}


int get_char() {
	char buff[1] = {0};
	_int80(3,0,buff,1,0,0);
	return buff[0];
}


void read(int fd,char* buffer,int size){
	_int80(3,fd,buffer,size,0,0);
}


void write(int fd,char* msg,int size){
	_int80(4,fd,msg,size,0,0);
}

void print_string(char* arr) {
	_int80(4,1,arr,strlen(arr),0,0);
}

void new_line(){
	_int80(5,0,0,0,0,0);
}

void clear_screen(){
	_int80(8,0,0,0,0,0);
}

void call_beep(){
		_int80(11,0,0,0,0,0);

}

void get_ticks(unsigned int * tick){
	_int80(12,0,0,0,tick,0);
}

