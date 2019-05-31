#include <videoDriver.h>



void printEntry(void *adr){
	char ch[10];

		 	uintToBase(adr,ch,10);
		 	drawString(ch,10);
		 	drawString("---",3);
		 	return;

}