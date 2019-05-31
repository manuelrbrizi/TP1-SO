#include "include/graphicsDriver.h"
#include "include/videoDriver.h"


extern int clock(int arg);

char ch[10] = {0};

void time(){


	int hour = (clock(04)+21)%24;
	int min = clock(2);
	int sec = clock(0);





	uintToBase(hour,ch,10);
	drawString(ch,2);
	drawString(":",1);

	uintToBase(min,ch,10);
	drawString(ch,2);
	drawString(":",1);


	uintToBase(sec,ch,10);
	drawString(ch,2);

}


void date(){
	int day = clock(7);
	int month = clock(8);
	int year = clock(9);

	uintToBase(day,ch,10);
	drawString(ch,2);
	drawString("/",1);

	uintToBase(month,ch,10);
	drawString(ch,2);
	
	drawString("/",1);
	
	uintToBase(year,ch,10);
	drawString(ch,2);
}


// void numToString(char * ch, int i){

//     char const digit[] = "0123456789";
//     char* p = ch;
//     if(i < 0){
//         *p++ = '-';
//         i *= -1;
//     }


//     int shifter = i;
//     do{ 
//         ++p;
//         shifter = shifter/10;
//     }while(shifter);
//     *p = '\0';

//     do{ 
//         *--p = digit[i%10];
//         i = i/10;
//     }while(i);


// }










