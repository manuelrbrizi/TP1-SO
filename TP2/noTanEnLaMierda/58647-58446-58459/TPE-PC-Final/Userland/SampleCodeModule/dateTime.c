extern void _int80(int desc);

void get_time(){
	_int80(6);
}

void get_date(){
	_int80(7);
}
