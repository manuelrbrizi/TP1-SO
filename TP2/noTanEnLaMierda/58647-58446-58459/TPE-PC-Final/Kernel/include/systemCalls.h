void writes(int fileDesc, char * buffer, int size);

void reads(int fileDesc, char * buffer, int size);

void new_line();

void get_time();

void get_date();

// void * system_malloc(int size, void ** ptr);
void * system_malloc(int size);

void system_free(void *ptr,int size);