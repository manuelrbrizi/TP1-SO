#include "include/pipe.h"
#include "include/memoryManager.h"

static pipe_t * pipe_list = (void*)0;

pipe_t * create_pipe(char * id, char * message, int bytes){
	pipe_t * p = malloc(4096);
	p->id = id;
	p->message = message;
	p->bytes = bytes;
	p->is_written = 0;
	p->read_only = 0;
	p->next = (void*)0;

	if(pipe_list == (void*)0){
		pipe_list = p;
	}
	else{
		pipe_t * aux = pipe_list;
		
		while(aux->next != (void*)0){
			aux = aux->next;
		}

		aux->next = p;
	}

	return p;
}

char * read_from_pipe(char * id){
	pipe_t * p = get_pipe(id);
	if(p == (void*)0){
		return (void*)0;
	}
	
	if(!(p->is_written)){
		return (void*)0;
	}

	return p->message;
}

int write_to_pipe(char * id, char * message){
	pipe_t * p = get_pipe(id);
	if(p == (void*)0){
		return 0;
	}

	if(p->read_only){
		return 0;
	}

	p->message = message;
	p->is_written = 1;
	return 1;
}

pipe_t * get_pipe(char * id){
	if(pipe_list == (void*)0){
		return (void*)0;
	}
	
	pipe_t * aux = pipe_list;
	while(aux != (void*)0 && aux->id != id){
		aux = aux->next;
	}

	return (void*)0;
}

int make_read_only(char * id){
	pipe_t * p = get_pipe(id);
	if(p == (void*)0){
		return 0;
	}

	p->read_only = 1;
}

