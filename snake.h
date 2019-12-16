#ifndef _SNAKE_H
#define _SNAKE_H
#define SNAKE_NODE_SIZE 5
#define DEFAULT_MOVE_SPEED 5
#include <math.h>

// 声明蛇结点结构体
typedef struct node {
	int x;
	int y;
	struct node* previous;
	struct node* next;
} Node;
typedef Node* Position;
typedef Node* Head;
typedef Node* Tail;
typedef int status;
typedef struct snake {
	Head head;
	Tail tail;
	int length;
	double xDirection;
	double yDirection;
	int velocity; // 蛇运动速度
}* Snake;

//status initHead(Head snakeHead);
status makeEmpty(Head snakeHead);
status insertByNode(int x, int y, Position node);
status insertByIndex(int x, int y, int index, Head snakeHead);
status checkExistence(Position node, Head snakeHead);
status deleteNode(Position node, Head snakeHead);
void traverse(Head snakeHead);
int getLength(Head snakeHead);
Position findNodeByIndex(int index, Head snakeHead);
status initSnake(Snake snake, int x, int y);
void drawSnake(Snake snake);
void drawNode(Position position);
void moveSnake(Snake snake);
void advanceNode(Position position);

#endif // !_Node_H
