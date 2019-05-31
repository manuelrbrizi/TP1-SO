typedef struct Balls {
	int x;
	int y;
	int degrees;
	int direction;
} Ball;

typedef struct Bars{
	int distance; //tomando la parte superior de la pantalla como el valor 0, es la distancia a el primer cuadradito que forma la barra
	int length; //cantidad de cuadraditos de la barra
	int x;
} Bar;

void playGame();
Ball setBall(int, int, int, int);
Bar setBar(int, int, int);
int willColide(Ball, Bar, Bar);
Ball calculateBallDirection(Ball, Bar, Bar, int);
void printAll(Ball, Bar, Bar);
//void printBall(int, int);
//void printBar(int, int, int);
//void printGame(Ball, Bar, Bar);