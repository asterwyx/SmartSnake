#ifndef _SNAKE_H
#define _SNAKE_H
#include <math.h>
#include "define.h"
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
Position findNodeByValue(int x, int y, Head snakeHead);
status initSnake(Snake snake, int x, int y);
void drawSnake(Snake snake);
void drawNode(Position position);
void moveSnake(Snake snake); // 实现整条蛇的移动
void advanceNode(Position position); // 当前结点设置为前一个结点的坐标，实现结点移动
void addTail(Snake snake); // 吃到食物后在适当位置加一个结点
void deleteOne(Snake snake);
void deleteHalf(Snake snake);

#endif // !_Node_H
