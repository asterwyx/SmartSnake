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
		// ���������ɵ�β��㵽ͷ����ϣ�ʹ��ͷ����previousָ��ָ��β��㣬����֮��ֱ�Ӳ����½��
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
	snakeHead->next = NULL; // ָ���ÿ�
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
	// ���ߵĸ�����Ա����г�ʼ��
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
	// �ʵ���λ����ָβ�������������һ���ߣ��Ҿ�����ȣ���ֻʣһ��ͷ����ʱ����ǰ������ķ��������
	Tail newTail = (Tail)malloc(sizeof(Node)); // �½�β���
	if (newTail != NULL)
	{
		if (snake->length == 1)
		{
			// ȷ���½����β����x,y�����ϵ�x,y��������ǰ�������ϵ������෴
			int deltaX = -snake->xDirection * SNAKE_NODE_SIZE * 2;
			int deltaY = -snake->yDirection * SNAKE_NODE_SIZE * 2;
			// ��ʼ��β���
			newTail->x = snake->tail->x + deltaX;
			newTail->y = snake->tail->y + deltaY;
		}
		else
		{
			// ��ͨ����£�ʹ���е������ϵ
			newTail->x = 2 * snake->tail->x - snake->tail->previous->x;
			newTail->y = 2 * snake->tail->y - snake->tail->previous->y;
		}
		// �ӵ�����ȥ
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
	// ɾ���������һ����㣬�������ȼ�һ��������㣬��ֱ�ӷ���
	if (snake == NULL)
	{
		perror("NULL snake");
		return;
	}
	if (snake->length == 0)
	{
		return; // ����Ϊ0ֱ�ӷ���
	}
	else
	{
		// �Ƚ����ȼ�һ
		snake->length--;
		// ɾ��β���
		Position tmpPos = snake->tail; // ��¼ԭ����β���
		snake->tail = tmpPos->previous; // �����µ�β���
		snake->tail->next = NULL; // ��������NULL
		free(tmpPos); // �ͷ����õ�β���
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
		// ֻ��һ��ͷ�������������Ҫ��snake��ͷβ���ָ��ҲҪ�ÿ�
		free(snake->head); // ֱ���ͷŵ�ͷ���
		snake->head = NULL;
		snake->tail = NULL; // ͷβָ���ÿ�
		snake->length = 0;
	}
	else
	{
		int halfLength = snake->length / 2; // ���һ��ĳ���
		Position newTail = findNodeByIndex(halfLength, snake->head); // ȷ����һ��ĳ��ȣ�һ�㳤��λ�õĽ��Ҳ�ͳ����µ�β���
		makeEmpty(newTail); // �ÿ��µ�β���֮������н��
		snake->tail = newTail; // �����µ�β���
		snake->length = halfLength; // �������ߵĳ���
	}
}

void resetSnake(Snake snake, int velocity)
{
	makeEmpty(snake->head);
	snake->tail = snake->head;
	snake->length = 1;
	snake->xDirection = INIT_XDIRECTION; // ���ó�ʼ����
	snake->yDirection = INIT_YDIRECTION; 
	snake->velocity = velocity; // ���ó�ʼ�ٶ�
	addTail(snake);
}

status checkSelf(Snake snake)
{
	return YES;
}


