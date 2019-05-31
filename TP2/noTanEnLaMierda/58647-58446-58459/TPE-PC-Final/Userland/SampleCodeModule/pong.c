//con W y S maneja el chico 1 y con O y L maneja el chico 2
//la barra debe ser de 5 cuadraditos, los dos superiores la tiran con una inclinacion de +45 grados ,los dos de abajo con una de -45 grados y el del medio con 0 grados
//la pelota comienza en el medio yendo en linea recta hacia la derecha
//               ---------X
//               |
//               |
//               |              ejes de crecimiento
//			     Y
#include "pong.h"
#include "include/stdInOut.h"
#include <stdlib.h>
#include "include/stringUtilities.h"
#include "include/graphics.h"
#define POSITION1 0 //POSICION1 es posicion inicial de la barra1 (comienzo pantalla)
#define POSITION2 1000//POSICION2 es posicion inicial de la barra2 (final pantalla)
//#define HEIGHT 758//alto
#define HEIGHT 608
#define WIDTH 1080 //ancho
#define DISTANCE_BEFORE_COLLITION 11 //numero maximo tal que si me muevo uno mas para la izquierda o para la derecha choco una barra o una pared
#define MOVEMENT 20 //pasos para arriba o abajo de la barra
#define LENGTH 150 //longitud de la barra
#define OFFSET 150

char buffy[10] = {0};

unsigned int * ticks;

//get_ticks(ticks);

void playGame(){
	print_string("    Left Player W/S || Right Player O/L || t to quit game || First to 3 wins!\n");
	Ball ball = setBall(WIDTH/2, OFFSET+HEIGHT/2, 0, 1);
	Bar bar1 = setBar((HEIGHT/2)+OFFSET-75, LENGTH, POSITION1);
	Bar bar2 = setBar((HEIGHT/2)+OFFSET-75, LENGTH, POSITION2);

	int i = 0;
	get_ticks(ticks);
	int initialTicks = *ticks;
	printAll(ball, bar1, bar2);

	//int totalScore = 0;
	int p1Score = 0;
	int p2Score = 0;

	while(p1Score < 3 && p2Score < 3){
		char input = get_char();
		//while(input == 0){ input = get_char();}

		if(input =='t' || input == 'T'){
			break;
		}

		if((input == 'w' || input == 'W') && bar1.distance >= 0+OFFSET){
			bar1.distance-=20;
		}

		else if((input == 's' || input == 'S' )&& bar1.distance <= HEIGHT - LENGTH+OFFSET){
			bar1.distance+=20;
		}

		else if((input == 'o' || input == 'O' )&& bar2.distance >= 0+OFFSET){
			bar2.distance-=20;
		}

		else if((input == 'l' || input == 'L') && bar2.distance <= HEIGHT -LENGTH+OFFSET){
			bar2.distance+=20;
		}
		i++;
		int collision = willColide(ball, bar1, bar2); //retorna + si colisiona con el bar1 y - si colisiona contra el bar2. El numero que devuelve es el cuadradito con el que va a chocar. Si es 0, no hay colision. Si es 100 impacta contra la pared superior, si es -100 impacta contra la pared inferior.

		get_ticks(ticks);
		if(*ticks - initialTicks >=1){
			initialTicks = *ticks; 	
			if(collision == 0){
				if(ball.degrees == 45){
					if(ball.direction == 1){
						ball.x = ball.x + MOVEMENT;
						ball.y = ball.y - MOVEMENT;
					}
				
					else{
						ball.x = ball.x - MOVEMENT;
						ball.y = ball.y - MOVEMENT;
					}
				}

				else if(ball.degrees == -45){
					if(ball.direction == 1){
						ball.x = ball.x + MOVEMENT;
						ball.y = ball.y + MOVEMENT;
					}
				
					else{
						ball.x = ball.x - MOVEMENT;
						ball.y = ball.y + MOVEMENT;
					}
				}

				else{
					if(ball.direction == 1)
						ball.x = ball.x + MOVEMENT;
					else
						ball.x = ball.x - MOVEMENT;
				}
			}

			else{
				ball = calculateBallDirection(ball, bar1, bar2, collision);
			}
		}

		printAll(ball, bar1, bar2);
		
		if(ball.x < POSITION1){
			p2Score += 1;
			ball = setBall((WIDTH+OFFSET)/2, OFFSET+(HEIGHT/2), 0, 1);

			// 			bar1 = setBar(HEIGHT/2, LENGTH, POSITION1);
			// bar2 = setBar(HEIGHT/2, LENGTH, POSITION2);

			
					//clear_screen();

			
			uintToBase(p1Score,buffy,10);
			print_string("    LEFT PLAYER SCORE: ");
			print_string(buffy);

			uintToBase(p2Score,buffy,10);
			print_string("       RIGHT PLAYER SCORE: ");
			print_string(buffy);
						new_line();

			call_beep();
		}

		else if(ball.x > POSITION2){
			p1Score += 1;
			ball = setBall((WIDTH+OFFSET)/2, OFFSET+(HEIGHT/2), 0, -1);

			uintToBase(p1Score,buffy,10);
			print_string("    LEFT PLAYER SCORE: ");
			print_string(buffy);

			uintToBase(p2Score,buffy,10);
			print_string("        RIGHT PLAYER SCORE: ");
			print_string(buffy);
						new_line();

			call_beep();
		}

	}

	clear_screen();

	if(p2Score>p1Score){
		print_string("Right Player Won!");
	}
	else if(p1Score > p2Score){
		print_string("Left Player Won!");
	}
	else{
		print_string("Do not try and win the game, that's impossible. Instead, only try to realize the \ntruth...there is no game. Then you'll see that it is not the game that is won, \nit is only yourself");
	}


}


Ball setBall(int x, int y, int degrees, int direction){
	Ball ball;
	ball.x = x;
	ball.y = y;
	ball.degrees = degrees;
	ball.direction = direction;
	return ball;
}

Bar setBar(int position, int length, int x){
	Bar bar;
	bar.distance = position;
	bar.length = length;
	bar.x = x;
	return bar;
}

int willColide(Ball ball, Bar bar1, Bar bar2){
	if(bar2.x-10 - ball.x < DISTANCE_BEFORE_COLLITION){
		if(ball.y > bar2.distance && ball.y < bar2.distance + bar2.length){
				int position = bar2.distance - ball.y;
				return position;
		}
	}

	else if(ball.x < DISTANCE_BEFORE_COLLITION+30){
		if(ball.y > bar1.distance && ball.y < bar1.distance + bar1.length){
				int position = ball.y - bar1.distance;
				return position;
		}
	}

	else if(HEIGHT - ball.y + OFFSET < DISTANCE_BEFORE_COLLITION){
		int x = 100;
		x *= -1;
		return x;
	}

	else if(ball.y - OFFSET < DISTANCE_BEFORE_COLLITION){
		return 100;
	}

	return 0;
}

Ball calculateBallDirection(Ball ball, Bar bar1, Bar bar2, int collision){

	Ball ball2;

	if(collision == 100){
		if(ball.direction == 1){
			ball2 = setBall(ball.x, ball.y + DISTANCE_BEFORE_COLLITION, -45, 1);
		}
		
		else{
			ball2 = setBall(ball.x, ball.y + DISTANCE_BEFORE_COLLITION, -45, -1);
		}
	}

	else if(collision == -100){
		if(ball.direction == 1){
			ball2 = setBall(ball.x, ball.y - DISTANCE_BEFORE_COLLITION, 45, 1);
		}

		else{
			ball2 = setBall(ball.x, ball.y - DISTANCE_BEFORE_COLLITION, 45, -1);
		}
	}

	else if(collision < 0){
		int index = -1 * collision;
		if(index <= LENGTH/2 - 1){
			ball2 = setBall(ball.x - DISTANCE_BEFORE_COLLITION, ball.y, 45, -1);
		}

		else if(index > LENGTH - LENGTH/1 - 1){
			ball2 = setBall(ball.x - DISTANCE_BEFORE_COLLITION, ball.y, -45, -1);
		}

		else{
			ball2 = setBall(ball.x - DISTANCE_BEFORE_COLLITION, ball.y, 0, -1);
		}
	}

	else{
		//printf("INDEX = %d\n", collision);
		if(collision < LENGTH/2 - 1){
			ball2 = setBall(ball.x + DISTANCE_BEFORE_COLLITION, ball.y, 45, 1);
		}

		else if(collision > LENGTH - LENGTH/1 - 1){
			ball2 = setBall(ball.x + DISTANCE_BEFORE_COLLITION, ball.y, -45, 1);
		}

		else{
			ball2 = setBall(ball.x + DISTANCE_BEFORE_COLLITION, ball.y, 0, 1);
			//return ball2;
		}
	}

	//return ball2;
}

void printAll(Ball ball, Bar bar1, Bar bar2){
	printBall(ball.x, ball.y);
	printBar(bar1.distance, bar1.length, bar1.x);
	printBar(bar2.distance, bar2.length, bar2.x);
}

/*void printBall(int x, int y){
	printf("printing ball\n");
	for(int i = 0; i < WIDTH; i++){
		
		for(int j = 0; j < HEIGHT; j++){
			
			if(x == i && y == j){
				printf("Ball: X = %d, Y = %d\n",i,j);
			}
		}
		
	}
}

void printBar(int distance, int length, int x){
printf("printing bar\n");
	for(int i = 0; i < WIDTH; i++){
		if(distance == i)
		printf("BAR X = %d, Y0 = %d, Y1 = %d\n",x,i,i+5);
	}
}*/

// void printGame(Ball ball, Bar bar1, Bar bar2){
// 	char * p;
// 	for(int i = 0; i < WIDTH; i++){
// 		for(int j = 0; j < WIDTH; j++){
// 			if(ball.x == i && ball.y == j){
// 				*p = "O";
// 			}

// 			else if(i >= bar1.distance && i <= bar1.distance + bar1.length && j == 0){
// 				*p = "X";
// 			}

// 			else if(i >= bar2.distance && i <= bar2.distance + bar2.length && j == WIDTH){
// 				*p = "X";
// 			}

// 			else{
// 				*p = " ";
// 			}

// 			p += 1;
// 		}
// 		*p = "\n";
// 		p += 1;
// 	}

// 	p += 1;
// 	*p = 0;
// 	print_string(p);
// }
