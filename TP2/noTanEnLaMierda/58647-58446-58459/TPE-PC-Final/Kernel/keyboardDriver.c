#include <videoDriver.h>
#include <scancodes.h>
#include <kernel.h>



extern char get_key();


#define SIZE 100

static int buffer[SIZE];
static int first = 0;
static int last = 0;

static int ctrl = 0;
static int shft = 0;
static int caps_lock = 0;


void update_buffer(){
	int key = get_key();

	switch(key){
			case 0x1D:
				ctrl = 1;
				break;

			case -99:
				ctrl = 0;
				break;

			case 0x2A:
			case 0x36:
				shft = 1;
				break;

			case -86:
			case -74:
				shft = 0;
				break;

			case 0x3A:
				caps_lock = 1-caps_lock;
				break;
	}
	int aux_char;



	if(key<0x4A && key>=0x00 && ascii_codes[key]!=0){
		if(shft){
			aux_char = shift_ascii_codes[key];
		}
		else{
			aux_char = ascii_codes[key];
		}

		if(caps_lock){
			if(aux_char <= 'z' && aux_char >= 'a'){
				aux_char = aux_char + 'A' - 'a';
			}
			else if(aux_char <= 'Z' && aux_char >= 'A'){
				aux_char = aux_char + 'a' - 'A';
			}
		}

		buffer[last++]=aux_char;

		if(last == 100){
			if(first >0){
				last = 0;
			}
		}

	}


}

void read_buffer(char * buff, int size){
	for(int i =0; i<size && last!=first ;i++){
		buff[i] = buffer[first+i];
		first++;
		buff++;
	}

	if(first == 100){
		first =0;
	}
}

void clear_buffer(){
	for(int i = 0; i<last; i++){
		buffer[i] = 0;
	}
}