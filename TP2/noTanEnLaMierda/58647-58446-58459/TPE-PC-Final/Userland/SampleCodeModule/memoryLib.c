extern void * _int80(int sys, int fileDesc, char* buffer, int size,unsigned int ** p1,void * ptr);	


void * malloc(int size){
	void * a;
	_int80(13,0,0,size,0,&a);
	return a;
}

void free(void *ptr, int size){
	_int80(14,0,0,size,0,ptr);
}