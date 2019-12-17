#include "snake.h"
#include <stdlib.h>
#include <easyx.h>
#include <stdio.h>

/*
status initHead(Head snakeHead)
{
	if (snakeHead == NULL)
	{
		return ERROR;
	}
	Tail tail = (Tail)malloc(sizeof(Snake));
	if (tail == NULL)
	{
		printf("Out of space!!!");
		return FAILURE;
	}
	else
	{
		// 链接新生成的尾结点到头结点上，使用头结点的previous指针指向尾结点，便于之后直接插入新结点
		tail->next = NULL;
		tail->previous = snakeHead;
		snakeHead->next = tail;
		snakeHead->previous = tail;
		return SUCCESS;
	}
}
*/
status makeEmpty(Head snakeHead)
{
	if (snakeHead == NULL)
	{
		perror("SnakeHead is NULL!!!");
		return ERROR;
	}
	Position tmp = snakeHead->next;
	while (tmp != NULL)
	{
		snakeHead->next = tmp->next;
		free(tmp);
		tmp = snakeHead->next;
	}
	snakeHead->next = NULL; // 指针置空
	return SUCCESS;
}

status insertByNode(int x, int y, Position node)
{
	if (node == NULL)
	{
		perror("Node is NULL!!!");
		return ERROR;
	}
	else
	{
		Position newNode = (Position)malloc(sizeof(Snake));
		if (newNode == NULL)
		{
			perror("Out of space!!!");
			return FAILURE;
		}
		else
		{
			newNode->x = x;
			newNode->y = y;
			newNode->previous = node;
			newNode->next = node->next;
			node->next->previous = newNode;
			node->next = newNode;
			return SUCCESS;
		}
	}
}

status insertByIndex(int x, int y, int index, Head snakeHead)
{
	if (snakeHead == NULL)
	{
		perror("SnakeHead is NULL!!!");
		return ERROR;
	}
	Position insPos = findNodeByIndex(index, snakeHead);
	if (insPos == NULL)
	{
		perror("NotFound");
		return ERROR;
	}
	else
	{
		return insertByNode(x, y, insPos->previous);
	}
}

Position findNodeByIndex(int index, Head snakeHead)
{
	if (snakeHead == NULL)
	{
		perror("SnakeHead is NULL!!!");
		return NULL;
	}
	Position tmp = snakeHead;
	for (int count = 0; count <= index; count++)
	{
		if (tmp == NULL)
		{
			break;
		}
		tmp = tmp->next;
	}
	return tmp;
}

Position findNodeByValue(int x, int y, Head snakeHead)
{
	Position position = snakeHead;
	while (position != NULL)
	{
		if (position->x == x && position->y == y)
		{
			return position;
		}
		position = position->next;
	}
	return NULL;
}

int getLength(Head snakeHead)
{
	if (snakeHead == NULL)
	{
		perror("SnakeHead is NULL!!!");
		return NULL;
	}
	Position tmp = snakeHead->next;
	int count = 0;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return count;
}

status deleteNode(Position node, Head snakeHead)
{
	if (checkExistence(node, snakeHead) == FAILURE)
	{
		perror("NotFound!!!");
		return ERROR;
	}
	else
	{
		Position previous = node->previous;
		Position next = node->next;
		previous->next = next;
		if (next != NULL)
		{
			next->previous = previous;
		}
		free(node);
		return SUCCESS;
	}
}

void traverse(Head snakeHead)
{
	
}

status checkExistence(Position node, Head snakeHead)
{
	Position tmp = snakeHead;
	while (tmp != NULL)
	{
		if (node == tmp)
		{
			return SUCCESS;
		}
		tmp = tmp->next;
	}
	return FAILURE;
}

status initSnake(Snake snake, int x, int y)
{
	if (snake == NULL)
	{
		perror("Snake is NULL!!!");
		return ERROR;
	}
	snake->head = (Head)malloc(sizeof(Node));
	snake->tail = (Tail)malloc(sizeof(Node));
	if (snake->head == NULL || snake->tail == NULL)
	{
		perror("Out of space!!!");
		return FAILURE;
	}
	// 对蛇的各个成员域进行初始化
	snake->head->x = x;
	snake->head->y = y;
	snake->xDirection = 1;
	snake->yDirection = 0;
	snake->tail->x = snake->head->x - 2 * SNAKE_NODE_SIZE;
	snake->tail->y = snake->head->y;
	snake->head->next = snake->tail;
	snake->tail->previous = snake->head;
	snake->head->previous = NULL;
	snake->tail->next = NULL;
	snake->length = 2;
	snake->velocity = DEFAULT_MOVE_SPEED;
	snake->hasWisdom = NO;
	return SUCCESS;
}

void drawSnake(Snake snake)
{
	Position position = snake->head;
	while (position != NULL)
	{
		drawNode(position);
		position = position->next;
	}
}

void drawNode(Position position)
{
	setfillcolor(SNAKE_COLOR);
	fillcircle(position->x, position->y, SNAKE_NODE_SIZE);
}

void moveSnake(Snake snake)
{
	Position position = snake->tail;
	while (position->previous != NULL)
	{
		advanceNode(position);
		position = position->previous;
	}
	snake->head->x += snake->velocity * snake->xDirection;
	snake->head->y += snake->velocity * snake->yDirection;
}

void advanceNode(Position position)
{
	if (position->previous != NULL)
	{
		position->x = position->previous->x;
		position->y = position->previous->y;
	}
}

void addTail(Snake snake)
{
	if (snake == NULL)
	{
		perror("NULL snake!!!");
		return;
	}
	// 适当的位置是指尾部三个结点连成一条线，且距离相等，当只剩一个头结点的时候，在前进方向的反方向添加
	Tail newTail = (Tail)malloc(sizeof(Node)); // 新建尾结点
	if (newTail != NULL)
	{
		if (snake->length == 1)
		{
			// 确定新结点在尾结点的x,y坐标上的x,y增量，和前进方向上的增量相反
			int deltaX = -snake->xDirection * SNAKE_NODE_SIZE * 2;
			int deltaY = -snake->yDirection * SNAKE_NODE_SIZE * 2;
			// 初始化尾结点
			newTail->x = snake->tail->x + deltaX;
			newTail->y = snake->tail->y + deltaY;
		}
		else
		{
			// 普通情况下，使用中点坐标关系
			newTail->x = 2 * snake->tail->x - snake->tail->previous->x;
			newTail->y = 2 * snake->tail->y - snake->tail->previous->y;
		}
		// 加到蛇上去
		snake->tail->next = newTail;
		newTail->previous = snake->tail;
		newTail->next = NULL;
		snake->tail = newTail;
		snake->length++;
	}
	else
	{
		perror("Out of space!!!");
		return;
	}
}

void deleteOne(Snake snake)
{
	// 删除蛇里面的一个结点，并将长度减一，如果是零，则直接返回
	if (snake == NULL)
	{
		perror("NULL snake");
		return;
	}
	if (snake->length == 0)
	{
		return; // 长度为0直接返回
	}
	else
	{
		// 先将长度减一
		snake->length--;
		// 删除尾结点
		Position tmpPos = snake->tail; // 记录原来的尾结点
		snake->tail = tmpPos->previous; // 设置新的尾结点
		snake->tail->next = NULL; // 重新设置NULL
		free(tmpPos); // 释放无用的尾结点
	}
}

void deleteHalf(Snake snake)
{
	if (snake == NULL)
	{
		perror("NULL snake!!!");
		return;
	}
	if (snake->length == 0)
	{
		return;
	}
	else if (snake->length == 1)
	{
		// 只有一个头结点的特殊情况，要将snake的头尾结点指针也要置空
		free(snake->head); // 直接释放掉头结点
		snake->head = NULL;
		snake->tail = NULL; // 头尾指针置空
		snake->length = 0;
	}
	else
	{
		int halfLength = snake->length / 2; // 算出一半的长度
		Position newTail = findNodeByIndex(halfLength, snake->head); // 确定了一半的长度，一般长度位置的结点也就成了新的尾结点
		makeEmpty(newTail); // 置空新的尾结点之后的所有结点
		snake->tail = newTail; // 设置新的尾结点
		snake->length = halfLength; // 设置新蛇的长度
	}
}

void resetSnake(Snake snake, int velocity)
{
	makeEmpty(snake->head);
	snake->tail = snake->head;
	snake->length = 1;
	snake->xDirection = INIT_XDIRECTION; // 设置初始方向
	snake->yDirection = INIT_YDIRECTION; 
	snake->velocity = velocity; // 设置初始速度
	addTail(snake);
}

status checkSelf(Snake snake)
{
	return YES;
}


