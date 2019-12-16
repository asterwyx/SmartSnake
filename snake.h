#ifndef _SNAKE_H
#define _SNAKE_H
#include <math.h>
#include "define.h"
// �����߽��ṹ��
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
	int velocity; // ���˶��ٶ�
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
void moveSnake(Snake snake); // ʵ�������ߵ��ƶ�
void advanceNode(Position position); // ��ǰ�������Ϊǰһ���������꣬ʵ�ֽ���ƶ�
void addTail(Snake snake); // �Ե�ʳ������ʵ�λ�ü�һ�����
void deleteOne(Snake snake);
void deleteHalf(Snake snake);

#endif // !_Node_H
