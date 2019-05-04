#include "include/scheduler.h"
#include "include/memoryManager.h"
#include "semaphor.h"

static Semaphor_t * semaphor_list = (void *)0;
extern tsl_lock_sem(int value);
extern tsl_unlock_sem(int value);

//creates a semaphor and savtsl_unlock_sem(aux->value);es it in the last position of the semaphor list
void sem_create(int sem_id, int initial_value){
	Semaphor_t sem = malloc(sizeof(Semaphor_t));
	sem.sem_id = sem_id;
	sem.value = initial_value;

	Semaphor_t * aux = semaphor_list;
	if(aux == (void*)0){
		aux = &sem;
	}

	else{
		while(aux->next != (void*)0){
			aux = aux->next;
		}

		aux->next =	&sem;
	}
}

// return 0 = failed to wait sem :: return 1 = sem waits correctly 
int sem_wait(int sem_id){
	Semaphor_t * aux = get_semaphor(sem_id);
	if(aux == (void*)0){
		return 0;
	}

	if(!aux->value){
		//crear el proceso  -  HACER FUNCION EN EL SCHEDULER QUE RETORNE EL PROCESO CORRIENDO
		int running_pid = get_running_process();
		Process * running_process = get_process(running_pid);

		if(aux->process_queue == (void*)0){
			aux->process_queue = running_process;
		}

		else{
			Process * aux_queue = aux->process_queue;

			while(aux_queue->next != (void*)0){
				aux_queue = aux_queue->next;
			}

			aux_queue->next = running_process;
			return 0; //process get locked by semaphor
		}
	}

	else{
		aux->value = 0;
		//ESTA FUNCION HAY QUE HACERLA CON EL COMANDO TSL EN ASSEMBLER, SETEAR EL SEMAFORO EN 0 Y NO DEJAR QUE OTRO PROCESO 
		//PUEDA MODIFICAR ESE VALOR
		tsl_lock_sem(aux->value);
		return 1; //process gets semaphor correctly
	}
}

int sem_post(int sem_id){
	Semaphor_t * aux = get_semaphor(sem_id);
	if(aux == (void*)0){
		return 0; //posted a non-existing semaphor
	}

	//ESCRIBIR ESTO EN ASM. USA EL COMANDO TSL PARA PONER ESE VALOR EN 0 Y QUE ALGUIEN MAS PUEDA USARLO
	tsl_unlock_sem(aux->value);

	if(aux->process_queue != (void*)0){
		//takes the first process of the queue, update the queue and process status.
		Process * next_process = aux->process_queue;
		aux->process_queue = aux->process_queue->next;
		next_process->status = READY;
	}
	else{
		//leaves semaphor ready to be waited.
		aux->value = 1;	
	}
	
	return 1; //semaphor posted correctly
}

Semaphor_t * get_semaphor(int sem_id){
	Semaphor_t * aux = semaphor_list;

	if(aux == (void *)0){
		return 0;
	}

	while(aux != (void *)0 && aux->value != sem_id){
		aux = aux->next;
	}

	return aux;
}