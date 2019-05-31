#include <videoDriver.h>


static void printEntry(void * adr);

void printEntry(void *adr){
	char ch[10];

		 	uintToBase(adr,ch,10);
		 	drawString(ch,1);

		 		newLine();
}