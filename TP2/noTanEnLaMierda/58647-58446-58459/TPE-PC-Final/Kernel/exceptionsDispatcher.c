#include <time.h>
#include <stdint.h>
#include <keyboardDriver.h>

#include <naiveConsole.h>

#include <videoDriver.h>

#include <idtLoader.h>

#include <graphicsDriver.h>

#include <kernel.h>


//extern char get_key();

void opCode(int stackPointer, int rip);
void zero_division(int stackPointer, int rip);
void print_regs(int stackPointer, int rip);



char c[20]={0};


void exceptionsDispatcher(int desc, int stackPointer, int rip) {
	switch (desc) {
		case 0:
			zero_division(stackPointer, rip);
			break;

		case 6:
			opCode(stackPointer, rip);
			break;
	}

	drawString("Restarting shell...\n",20);

	//init_shell();

	return;
}


void zero_division(int stackPointer, int rip){
	drawString("  [ZERO DIVISION EXCEPTION] >> You can't divide by zero!",58);
	newLine();
	newLine();

	print_regs(stackPointer,rip);



}


void opCode(int stackPointer, int rip){

	drawString("  [INVALID OPCODE EXCEPTION] >> Unrecognized OpCode!",52);


	newLine();
	newLine();

	print_regs(stackPointer,rip);
}

void print_regs(int stackPointer, int rip){

	drawString("        [RIP: ",14);

		uintToBase(rip,c,10);

	drawString(c,10);
	drawString("]",1);
	newLine();
	newLine();


	drawString("        [RSP: ",14);

	uintToBase(stackPointer,c,10);

	drawString(c,10);
	
	drawString("]",1);
	newLine();

}
