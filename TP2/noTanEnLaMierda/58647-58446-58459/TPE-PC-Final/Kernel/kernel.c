#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <videoDriver.h>

#include <time.h>

#include <clock.h>

#include <graphicsDriver.h>

//#include "include/videoDriver.h"

#include <interrupts.h>

#include <keyboardDriver.h>

#include "include/memoryManager.h"
#include "scheduler.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

extern char get_key();

void init_shell();

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	
	clearBSS(&bss, &endOfKernel - &bss);

	

	return getStackBase();
}

int main()
{	
	load_idt();
	int tick = 0;
	int i = 0;
	newLine();
	drawString("---------------------------------------------------------------------\0",100);
	newLine();
	drawString("Welcome to The Ricefields OS!\0",100);
	newLine();
	drawString("Everything seems to be working.\0",100);
	newLine();
	drawString("Get ready to meet shell!\0",100);

	newLine();

	drawString("---------------------------------------------------------------------\0",100);

	newLine();

	ticks_elapsed();
		newLine();



	char  ch[10] = {0};

	while(1){
		 if(tick == i){

		 	uintToBase(5-i,ch,10);
		 	drawString(ch,1);

		 		newLine();

		 	i++;
		}
		if(tick == 6){
			clear();
			clear_buffer();
			init_shell();
		}
		if(tick == 5){
			drawString("0110101",7);

		}
		tick = seconds_elapsed();


	}



	return 0;
}

void init_shell(){

	startMemoryManager();

	//void *a = malloc(5000);

	void * rsp = queue_new_process(200, sampleCodeModuleAddress);


	//schedule(rsp, 0);
	//((EntryPoint)sampleCodeModuleAddress)();
}



