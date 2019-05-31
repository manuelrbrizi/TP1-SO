#include <time.h>
#include <graphicsDriver.h>

extern void beep();
extern void stopsound();

void play_beep(){
	 //int t = seconds_elapsed();  No lo puedo hacer por timer tick porque por algun motivo no tickea cuando corres la rutina de beep
	 //t += 1;

	beep();
	double t = 99999;

	while(t>0){
		t -= 0.02;

	}

	stopsound();

}
