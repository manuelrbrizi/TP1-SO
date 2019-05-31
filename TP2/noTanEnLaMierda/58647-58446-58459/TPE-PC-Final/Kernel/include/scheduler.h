typedef struct Process{
	int pid;
	void * rsp;
	int tickets;
	int state;
	struct Process * next;
} Process_t;

Process_t * pick_a_winner();
void update_ticket_list();
int calculate_tickets(int tickets);
Process_t * get_process(int pid);
void delete_process(int pid);
void * schedule(void * rsp, int process_finished);
void * queue_new_process(int tickets, void * entryPoint);
