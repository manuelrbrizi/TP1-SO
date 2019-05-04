typedef struct Semaphor {
	int value = 0;
	int sem_id = 0;
	Process_t * process_queue = (void*)0;
	Semaphor * next = (void*)0;
} Semaphor_t;

void sem_create(int sem_id, int initial_value);
int sem_wait(int sem_id);
int sem_post(int sem_id);
Semaphor_t * get_semaphor(int sem_id);
