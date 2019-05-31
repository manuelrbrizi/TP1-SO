//PREGUNTAS

//tengo que guardar yo el estado en el que va a quedar el proceso luego de desalojado? 
//o lo tengo que obtener desde las cosas que se guardan en el stack?

//con la funcion calculate_tickets vamos a tener problemas si un proceso que termino queda almacenado en, por ejemplo
//la posicion 99 porque con ceil podes quedar n veces atras (siendo n la cantidad de programas). si justo le toca el ticket, explota todo

//como se cuando pongo el estado waiting?

#include <time.h>
#include "include/scheduler.h"
#include "videoDriver.h"
#include "graphicsDriver.h"
#include "include/memoryManager.h"

extern void * init_process_stack(void * rsp, void * entry_point);


//Process struct


//States
#define READY 0
#define WAITING 1
#define RUNNING 2

//Used variables for scheduler
static int PROCESS_QUANTITY = 0;
static int TOTAL_TICKETS = 0;
static int MAX_TICKETS = 0;
static int ticket_list[100];
static int FLAG = 0;
static int NEXT_PID = 0;
static Process_t * process_list;
static int CURRENT_PID = 0;
static int SHELL_STARTED = 0;
//Function implementations

Process_t * get_process(int pid){
	//no valido si es null porque es un metodo privado
	Process_t * p = process_list;
	while(p->next != (void*)0 && p->pid != pid){
		p = p->next;
	}	
	return p;
}

void delete_process(int pid){
	Process_t * p = process_list;
	
	while((*(p->next)).pid != pid){
		p = p->next;
	}	
	
	p->next = (p->next)->next;
}

//updates a running process rsp and returns a ready process rsp
void * schedule(void * rsp, int process_finished){

//drawString("AAA",3);
	if(PROCESS_QUANTITY == 0){
		return rsp;
	}
	if(!SHELL_STARTED && PROCESS_QUANTITY == 1){
		char ch[10];
		uintToBase(process_list->rsp,ch,10);
		drawString(ch,10);

		SHELL_STARTED = 1;
		return process_list->rsp;
	}

	if(process_finished){
		delete_process(CURRENT_PID);
		update_ticket_list();

	}

	else{
		Process_t * p = get_process(CURRENT_PID);
		p -> rsp = rsp;
		p -> state = READY;
	}

	//buscamos un proceso ganador
	Process_t * q = pick_a_winner();
	while(q -> state != READY){
		q = pick_a_winner();

	}




	q -> state = RUNNING;
	CURRENT_PID = q->pid;

	return q->rsp;
}

//add to list a new process
void * queue_new_process(int tickets,void * entryPoint){

	//CREAR STACK DE MENTIRA
	void * mal =  malloc(4000);



	void * rsp = init_process_stack(mal,entryPoint);

	NEXT_PID++;


	Process_t * p = malloc(sizeof(Process_t));
	p->pid = NEXT_PID;
	p->rsp = rsp;
	p->tickets = tickets;
	p->state = READY;
	p->next = (void*)0;

	

	if(process_list == (void*)0){
		process_list = p;
	}

	else{
		Process_t * auxiliar = process_list;
		while(auxiliar->next != (void*)0){
			auxiliar = auxiliar->next;
		}

		auxiliar->next = p;
	}

	PROCESS_QUANTITY = PROCESS_QUANTITY +1;
	//PROCESS_QUANTITY++;
	TOTAL_TICKETS += tickets;

	//CURRENT_PID = p->pid;

	update_ticket_list();

	// char ch[10];
	// uintToBase(rsp,ch,10);
	// drawString(ch,10);

	return rsp;

}

//select a winner ticket, cdigo de github
Process_t * pick_a_winner(){
	if(!FLAG){
		//srand(time(0));
		FLAG = 1;	
	}

	//int ticket = rand()%MAX_TICKETS;
	int ticket = 10;
	int pid = ticket_list[ticket];
	return get_process(pid);
}

//la idea es mantener una lista "ticket_list" que tenga 100 posiciones donde cada una almacene el pid del proceso que tiene el ticket
//si un proceso tiene el 20% del cpu, tendra su pid en 20 posiciones de ticket_list
void update_ticket_list(){
	int i, j, counter = 0;
	Process_t * p = process_list;
	
	for(i = 0; i < PROCESS_QUANTITY; i++){
		int cpu_fraction = calculate_tickets(p->tickets);

		for(j = 0; j < cpu_fraction; j++){
			ticket_list[j + counter] = p->pid;
		}
		counter += cpu_fraction;

		if(p->next == (void*)0){
			break;
		}

		p = p->next;
	}

	MAX_TICKETS = counter;
}

//ESTA FUNCION YA FUNCIONA SIN CEIL Y SIN FLOOR, ESTA PROBADA POSTA 100% REAL NO FAKE

//returns percentage of cpu required for that process
int calculate_tickets(int tickets){
	double decimal_tickets = (tickets*100)/TOTAL_TICKETS;
	int truncated_decimal_tickets = (tickets*100)/TOTAL_TICKETS;

	if(decimal_tickets - (double)truncated_decimal_tickets >= 0.5){
		return truncated_decimal_tickets + 1;
	}

	return truncated_decimal_tickets;
}
