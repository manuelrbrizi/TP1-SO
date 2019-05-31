#include "include/shell.h"
#include "include/stdInOut.h"
#include "include/stringUtilities.h"

#include "include/pong.h"
#include "include/dateTime.h"

#include "include/memoryLib.h"

	char buff[100] = {0};
	char last_command[100] = {0};
	int cursorRow = 0;
	int cursorCol = 0;

	static int first = 0;

	static int last = 0;
	//static int z = 0;

	char * help_prompt = " help -> Display this message\n        time -> Get system's time\n        date -> Get system's date\n        clear -> clears shell\n        welcome -> play welcome_message animation\n        pong -> play Pong!\n        beep -> play BEEP\n        zero -> Test the divide by zero exception\n        opcode -> Test the Invalid OpCode exception\n        info -> Credits!\n        You can use the UpArrow to access last command!";

	static char * info_prompt = " The RiceFields OS V1.0.\n        Architects: \n                Baader, Juan Martin. \n                Bergagna, Federico.\n                Rodriguez Brizi, Manuel\n\0";
	extern void int10(void);
	extern void throw_opcode_exception(void);

	void zero_exception();
	void opcode_exception();
	void help_inst();
	void copy_buff(char * from, char *to);
	void welcome_message();
	void new_shell_line();
	void clear_shell();
	void start_shell();



void run_command(){

	copy_buff(buff, last_command);

	buff[last]='\0';


	char * time = "time\0";
	char * date = "date\0";
	char * zero = "zero\0";
	char * help = "help\0";
	char * clear = "clear\0";
	char * welcome = "welcome\0";
	char * pong = "pong\0";
	char * beep = "beep\0";
	char * opcode = "opcode\0";
	char * info = "info\0";
	char * mallocs = "malloc\0";
	char * frees = "free\0";
		char * mallocs2 = "malloc2\0";


	if(strcmp(time,buff)){
		get_time();
	}
	else if(strcmp(date,buff)){
		get_date();
	}
	else if(strcmp(zero,buff)){
		zero_exception();
	}
	else if(strcmp(help,buff)){
		help_inst();
	}
	else if(strcmp(clear, buff)){
		clear_shell();
	}
	else if(strcmp(welcome,buff)){
		welcome_message();
	}
	else if(strcmp(pong,buff)){
		clear_shell();
		playGame();
	}
	else if(strcmp(beep,buff)){
		call_beep();
	}
	else if(strcmp(opcode, buff)){
		opcode_exception();
	}
	else if(strcmp(info,buff)){
		print_string(info_prompt);
	}
	else if(strcmp(mallocs, buff)){

		void * add = malloc(5000);
	}
	else if(strcmp(mallocs2, buff)){
		char * add = (char *)malloc(10000);
	}

	else if(strcmp(frees,buff)){
		free((void *) 0x700000,5000);


	}
	else{
		print_string("INVALID COMMAND");
	}

	last=0;
}

void zero_exception(){
	int i = 10/0;
	return;
}

void opcode_exception(){
	throw_opcode_exception();
}

void help_inst(){
	print_string(help_prompt);
}

void copy_buff(char * from, char *to){
	for(int i = 0; i<last;i++){
		to[i] = from[i];
	}
}


void welcome_message(){
	char * msg = "Wake up Neo...\0";
	int i = 0;
	while(1){
		if(*msg == '\0'){
			break;
		}
		if(i == 20000000){
			put_char(*msg);
			msg++;
			i=0;
		}
		i++;
	}
}

void new_shell_line(){
	new_line();
	print_string("Neo $> ");
}

void clear_shell(){
	clear_screen();
}

void start_shell(){

		int c = 0;
			//print_string("shell");
			//						print_string("shell");

			//welcome_message();
			//			print_string("shell");


			new_shell_line();
			print_string(help_prompt);

			new_shell_line();


	while(1){

		c = get_char();
		if(c!=0){
			if(c == '\n'){
				if(first<last){
					new_shell_line();
					run_command();
					new_shell_line();
				}
				else{
					new_shell_line();
				}
			}
			else if(c == '\b'){
				if(last>0){
					put_char(c);
					last--;
				}
			}
			else if(c == '/'){
				copy_buff(last_command,buff);
				print_string(buff);
				last = strlen(buff);
			}
			else{
				buff[last] = c;
				put_char(c);
				last++;
			}
		}

	}
}


