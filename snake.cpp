#include "snake.h"
#include <stdlib.h>
#include <stdio.h>
#define SUCCESS 0
#define FAILURE 1
#define ERROR -1
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
	while (tmp != snakeHead->previous)
	{
		snakeHead->next = tmp->next;
		free(tmp);
		tmp = snakeHead->next;
	}
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
			printf("Out of space!!!");
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
		insertByNode(x, y, insPos->previous);
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
		next->previous = previous;
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

status initSnake(Snake snake)
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
	snake->head->next = snake->tail;
	snake->tail->previous = snake->head;
	snake->head->previous = snake->tail;
	return SUCCESS;
}