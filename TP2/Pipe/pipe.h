typedef struct pipe{
	char * id;
	char * message;	
	int bytes;
	int is_written;
	int read_only;
	struct pipe * next;
} pipe_t;

pipe_t * create_pipe(char * id, char * message, int bytes);
char * read_from_pipe(char * id);
pipe_t * get_pipe(char * id);
int write_to_pipe(char * id, char * message);