//#include <naiveConsole.h>
#include "include/videoDriver.h"

extern int clock(int arg);

//static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

static const int screen_limit = 0xB8FA0;

void clearLastLine();
void vdNewline();
void vdPrintChar(char character);
void vdPrintCharColoured(char character, int colour);
void vdPrintBase(uint64_t value, uint32_t base);





// void drawPixel(int row, int col, int color){

// 	int loc = calculateScreenPoint(row,col)+1;
// 	video[loc] = color;

// }

int calculateScreenPoint(int row, int col){
	return 2*((80*row )+ col);
}


void updateScreen(){
	
	if(currentVideo >= 0xB8FA0){
		for(int i = 0; i<2*80*25;i++){
			video[i] = video[i+160];

		}
		clearLastLine();
		currentVideo = 0xB8FA0 - 0xA0;
	}
	
	//vdPrintChar(video[0]);
}


void clearLastLine(){
	for(int i = (height-1)*width; i<height*width;i++){
		video[2*i] = ' ';
	}
}


void vdPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		if(string[i]=='\n'){
			vdNewline();
		}
		else{
			vdPrintChar(string[i]);
		}
}

void vdPrintColoured(const char * string, int colour)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		vdPrintCharColoured(string[i], colour);
}

void vdPrintChar(char character)
{	
	updateScreen();
	if(character != '\b'){
		*currentVideo = character;
		currentVideo += 2;
	}
	else if(currentVideo>0xB8000){
		currentVideo -= 2;
		*currentVideo = 0;
	}

}

void vdPrintCharColoured(char character, int colour)
{
	*currentVideo = character;
	currentVideo += 1;
	*currentVideo = colour;
	currentVideo += 1;
}

void vdNewline()
{
	do
	{
		vdPrintChar(' ');
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void vdPrintDec(uint64_t value)
{
	vdPrintBase(value, 10);
}

void vdPrintHex(uint64_t value)
{
	vdPrintBase(value, 16);
}

void vdPrintBin(uint64_t value)
{
	vdPrintBase(value, 2);
}

void vdPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    vdPrint(buffer);
}

void vdClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i * 2] = ' ';
	currentVideo = video;
}

 uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
