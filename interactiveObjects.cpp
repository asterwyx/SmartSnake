#include "interactiveObjects.h"
#include <stdlib.h>
#include "define.h"
status initObject(PtrToObject o, Kind type)
{
	// ��ͬ���ߣ�Object��ͷ����ǿյģ��ӵڶ�����㿪ʼ�洢��Ϣ
	if (o == NULL)
	{
		perror("NULL object!!!");
		return ERROR;
	}
	// ��ʼ��ͷ����β���
	o->head = (PtrToNode)malloc(sizeof(O_Node));
	// o->tail = (PtrToNode)malloc(sizeof(O_Node));
	if (o->head != NULL)
	{
		o->tail = o->head;
		o->head->previous = NULL;
		o->head->next = NULL;
		o->size = 0; // ��ʼ����С
		// ��ʼ�������Ĳ���
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
		o->type = type; // ��ʼ��Ϊ���������
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
	head->next = NULL; // ָ���ÿ�
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
				// λ�ھ�����߽�����
				if (snake->head->y < result->y)
				{
					// λ�ھ����ϱ߽�����棬������λ�����Ͻ�
					if (dist(snake->head->x, snake->head->y, result->x, result->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else if (snake->head->y > (result->y + o->parameters[1]))
				{
					// λ�ھ����±߽�����棬������λ�����½�
					if (dist(snake->head->x, snake->head->y, result->x, result->y + o->parameters[1]) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else
				{
					// λ�ھ��ε����±߽��м䣬������λ�ھ��ε����
					if ((result->x - snake->head->x) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
			}
			else if (snake->head->x > (result->x + o->parameters[0]))
			{
				// λ�ھ����ұ߽���ұ�
				if (snake->head->y < result->y)
				{
					// λ�ھ����ϱ߽�����棬������λ�����Ͻ�
					if (dist(snake->head->x, snake->head->y, result->x + o->parameters[0], result->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else if (snake->head->y > (result->y + o->parameters[1]))
				{
					// λ�ھ����±߽�����棬������λ�����½�
					if (dist(snake->head->x, snake->head->y, result->x + o->parameters[0], result->y + o->parameters[1]) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else
				{
					// λ�ھ��ε����±߽��м䣬������λ�ھ��ε��ұ�
					if ((snake->head->x - result->x) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
			}
			else
			{
				// λ�ھ������ұ߽���м�����
				if (snake->head->y < result->y)
				{
					// λ�ھ����ϱ߽�����棬������λ��������
					if ((result->y - snake->head->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else if (snake->head->y > (result->y + o->parameters[1]))
				{
					// λ�ھ����±߽�����棬������λ��������
					if ((snake->head->y - result->y) < SNAKE_NODE_SIZE)
					{
						break;
					}
				}
				else
				{
					// λ�ھ��ε����±߽��м䣬������λ�ھ��ε��м�
					break;
				}
			}
			result = result->next; // ������һ�����
		}
	}
	
	return result;
}
