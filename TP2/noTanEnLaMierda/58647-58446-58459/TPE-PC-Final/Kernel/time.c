#include <time.h>
#include <stdint.h>
#include "include/scheduler.h"


static unsigned long ticks = 0;

uint64_t timer_handler(uint64_t rsp) {
	ticks++;
	//save_context();
	void * new_rsp = schedule((void*)rsp, 0);
	//get_context();

	return (uint64_t) new_rsp;

}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
