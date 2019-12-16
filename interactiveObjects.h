#ifndef _INTERACTIVE_OBJECTS_H
#define _INTERACTIVE_OBJECTS_H
#include "define.h"
#include "snake.h"
// 表示互动物体的单向链表
typedef struct o_node {
	int x;
	int y;
	struct o_node* previous;
	struct o_node* next;
} O_Node;
typedef O_Node* PtrToNode;
typedef enum kind
{
	FOOD,
	MINE,
	POISONOUSWEEDS,
	WISDOMGRASS,
	WALL
} Kind;
typedef struct object {
	PtrToNode head;
	PtrToNode tail;
	int size;
	Kind type;
} Object;
typedef Object* PtrToObject;
typedef PtrToObject Food; // 食物
typedef PtrToObject Mine; // 地雷
typedef PtrToObject PoisonousWeeds; // 毒草
typedef PtrToObject WisdomGrass; // 智慧草
typedef PtrToObject Wall;


status initObject(PtrToObject o, Kind type);
status isEmpty(PtrToObject o);
status o_makeEmpty(PtrToNode head);
status o_insertByNode(int x, int y, PtrToNode node);
status o_insertByIndex(int x, int y, int index, PtrToNode head);
status o_deleteNode(PtrToNode node, PtrToNode head);
status o_checkExistence(PtrToNode node, PtrToNode head);
PtrToNode o_findNodeByIndex(int index, PtrToNode head);
PtrToNode o_findNodeByValue(int x, int y, PtrToNode head);
PtrToNode checkCollision(PtrToObject o, Snake snake);
#endif // !_INTERACTIVE_OBJECTS_H
