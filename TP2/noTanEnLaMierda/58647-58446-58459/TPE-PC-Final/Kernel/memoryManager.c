#include <videoDriver.h>

#define PAGESIZE 4096
#define MAXPAGES 100

static void * addresses[MAXPAGES];
static int sizes[MAXPAGES];
static int last_idx = 0;

static 	char ch[10];

void add(void * address,int size);

void fix_arrays(int from);


void startMemoryManager(){
	addresses[0] = (void *) 0x700000;
	sizes[0] = MAXPAGES;
	last_idx++;
}

void * malloc(int byte_size){



	int size = byte_size/PAGESIZE;
	size++;

	int best_index=0;

	for(int i = 0; i<last_idx;i++){
		if(sizes[i] == size){
			best_index = i;
			break;
		}
		else if(sizes[i] > size && sizes[i]<sizes[best_index]){
			best_index = i;
		}
	}


		void * best_address = addresses[best_index];


	if(size < sizes[best_index]){


		addresses[best_index] = (addresses[best_index]) + (size*PAGESIZE);

		sizes[best_index] = (sizes[best_index]) - size;
	

		return best_address;
	}
	else if(size == sizes[best_index]){
		fix_arrays(best_index);

		return best_address;
	}
	else{
	
		return (void *) 0;
	}

	

}


void free(void * address, int byte_size){

			drawString("fre",3);

	int size = byte_size/PAGESIZE;
	size++;				


	for(int i = 0;i<last_idx;i++){
		if(addresses[i] > address){
			if(last_idx > 1 && address + size*PAGESIZE == addresses[i] && addresses[i-1] + sizes[i-1]*PAGESIZE == address){
				sizes[i-1] = sizes[i-1] + size + sizes[i];
				fix_arrays(i);
				last_idx--;
				break;
			}
			else if(address + size*PAGESIZE == addresses[i]){
				addresses[i] = address;
				sizes[i]+=size;
				break;
			}
			else if(addresses[i-1] + sizes[i-1]*PAGESIZE == address){
				sizes[i-1] += size;
				break;
			}
			else{
				add(address,size);
				break;
			}
		}
	}
}


void add(void * address,int size){

			drawString("add",3);


	int i;
	for(i = last_idx-1; (i>=0 && addresses[i] > address);i--){
		addresses[i+1] = addresses[i];
		sizes[i+1] = sizes[i];
	}

	addresses[i+1] = address;
	sizes[i+1] = size;

	last_idx++;

}


void fix_arrays(int from){
			drawString("fix",3);

	for(int i = from; i<last_idx-1;i++){
		addresses[i] = addresses[i+1];
		sizes[i] = sizes[i+1];
	}
}
