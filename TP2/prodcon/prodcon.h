struct area
{
	void* initial;
	int current_reading;
	int current_writing;
};

void producer(struc area currentarea);
void consumer(struct area currentarea);
