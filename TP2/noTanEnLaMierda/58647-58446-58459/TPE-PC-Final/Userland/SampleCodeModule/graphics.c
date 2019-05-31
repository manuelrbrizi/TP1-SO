extern void _int80(int sys, int fileDesc, char* buffer, int size);


void draw_pixel(int x, int y){
	_int80(9,x,0,y);
}

void printBall(int x, int y){
	draw_pixel(x,y);
}

void printBar(int distance, int length, int x){
	// for(int i = 0; i<length;i++){
	// 	draw_pixel(x,distance+i);
	// }
	_int80(10,x,0,distance);
}

