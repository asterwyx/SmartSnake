#include "interactiveObjects.h"
#include <stdlib.h>
#include "define.h"
status initObject(PtrToObject o, Kind type)
{
	// 不同于蛇，Object的头结点是空的，从第二个结点开始存储信息
	if (o == NULL)
	{
		perror("NULL object!!!");
		return ERROR;
	}
	// 初始化头结点和尾结点
	o->head = (PtrToNode)malloc(sizeof(O_Node));
	// o->tail = (PtrToNode)malloc(sizeof(O_Node));
	if (o->head != NULL)
	{
		o->tail = o->head;
		o->head->previous = NULL;
		o->head->next = NULL;
		o->size = 0; // 初始化大小
		// 初始化各个的参数
		switch (type)
		{
		case MINE:
			o->parameters[0] = MINE_NODE_SIZE;
			o->parameters[1] = 0;
			break;
		case FOOD:
			o->parameters[0] = FOOD_NODE_WIDTH;
			o->parameters[1] = FOOD_NODE_HEIGHT;
			break;
		case POISONOUSWEEDS:
			o->parameters[0] = GRASS_NODE_WIDTH;
			o->parameters[1] = GRASS_NODE_HEIGHT;
			break;
		case WISDOMGRASS:
			o->parameters[0] = GRASS_NODE_WIDTH;
			o->parameters[1] = GRASS_NODE_HEIGHT;
			break;
		case WALL:
			o->parameters[0] = WALL_NODE_WIDTH;
			o->parameters[1] = WALL_NODE_HEIGHT;
			break;
		default:
			break;
		}
		o->type = type; // 初始化为给定的类别
		return SUCCESS;
	}
	else
	{
		perror("Out of space!!!");
		return FAILURE;
	}

}

status isEmpty(PtrToObject o)
{
	if (o == NULL)
	{
		perror("NULL object!!!");
		return ERROR;
	}
	else
	{
		if (o->size == 0)
		{
			return YES;
		}
		else
		{
			return NO;
		}
	}
}

status o_makeEmpty(PtrToNode head)
{
	if (head == NULL)
	{
		perror("SnakeHead is NULL!!!");
		return ERROR;
	}
	PtrToNode tmp = head->next;
	while (tmp != NULL)
	{
		head->next = tmp->next;
		free(tmp);
		tmp = head->next;
	}
	head->next = NULL; // 指针置空
	return SUCCESS;
}

status o_insertByNode(int x, int y, PtrToNode node)
{
	if (node == NULL)
	{
		perror("Node is NULL!!!");
		return ERROR;
	}
	else
	{
		PtrToNode newNode = (PtrToNode)malloc(sizeof(O_Node));
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

status o_insertByIndex(int x, int y, int index, PtrToNode head)
{
	if (head == NULL)
	{
		perror("Head is NULL!!!");
		return ERROR;
	}
	PtrToNode insPos = o_findNodeByIndex(index, head);
	if (insPos == NULL)
	{
		perror("NotFound");
		return ERROR;
	}
	else
	{
		return o_insertByNode(x, y, insPos->previous);
	}
}

status o_deleteNode(PtrToNode node, PtrToNode head)
{
	if (o_checkExistence(node, head) == FAILURE)
	{
		perror("NotFound!!!");
		return ERROR;
	}
	else
	{
		PtrToNode previous = node->previous;
		PtrToNode next = node->next;
		previous->next = next;
		next->previous = previous;
		free(node);
		return SUCCESS;
	}
}

status o_checkExistence(PtrToNode node, PtrToNode head)
{
	PtrToNode tmp = head;
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

PtrToNode o_findNodeByIndex(int index, PtrToNode head)
{
	if (head == NULL)
	{
		perror("SnakeHead is NULL!!!");
		return NULL;
	}
	PtrToNode tmp = head;
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

PtrToNode o_findNodeByValue(int x, int y, PtrToNode head)
{
	PtrToNode position = head;
	while (position != NULL)
	{
		if (position->x == x && position->y == y)
		{
			return position;
		}
		position = position->next;
	}
}

PtrToNode checkCollision(PtrToObject o, Snake snake)
{
	if (snake == NULL || o == NULL)
	{
		perror("NULL snake");
		return NULL;
	}
	PtrToNode result = o->head->next;
	if (o->type == MINE)
	{
		while (result != NULL)
		{
			if (dist(result->x, result->y, snake->head->x, snake->head->y) < (SNAKE_NODE_SIZE + MINE_NODE_SIZE))
			{
				break;
			}
			result = result->next;
		}
	}
	else
	{
		while (result != NULL)
		{
			if (snake->head->x < result->x)
			{
				// 位于矩形左边界的左边
				if (snake->head->y < result->y)
				{
					// 位于矩形上边界的上面，整体上位于左上角
					if (dist(snake->head->x, snake->head->y, result->x, result->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else if (snake->head->y > (result->y + o->parameters[1]))
				{
					// 位于矩形下边界的下面，整体上位于左下角
					if (dist(snake->head->x, snake->head->y, result->x, result->y + o->parameters[1]) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else
				{
					// 位于矩形的上下边界中间，整体上位于矩形的左边
					if ((result->x - snake->head->x) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
			}
			else if (snake->head->x > (result->x + o->parameters[0]))
			{
				// 位于矩形右边界的右边
				if (snake->head->y < result->y)
				{
					// 位于矩形上边界的上面，整体上位于右上角
					if (dist(snake->head->x, snake->head->y, result->x + o->parameters[0], result->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else if (snake->head->y > (result->y + o->parameters[1]))
				{
					// 位于矩形下边界的下面，整体上位于右下角
					if (dist(snake->head->x, snake->head->y, result->x + o->parameters[0], result->y + o->parameters[1]) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else
				{
					// 位于矩形的上下边界中间，整体上位于矩形的右边
					if ((snake->head->x - result->x) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
			}
			else
			{
				// 位于矩形左右边界的中间区域
				if (snake->head->y < result->y)
				{
					// 位于矩形上边界的上面，整体上位于正上面
					if ((result->y - snake->head->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else if (snake->head->y > (result->y + o->parameters[1]))
				{
					// 位于矩形下边界的下面，整体上位于正下面
					if ((snake->head->y - result->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else
				{
					// 位于矩形的上下边界中间，整体上位于矩形的中间
					break;
				}
			}
			result = result->next; // 遍历后一个结点
		}
	}
	
	return result;
}
