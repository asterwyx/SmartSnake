#ifndef _INTERACTIVE_OBJECTS_H
#define _INTERACTIVE_OBJECTS_H
#include "define.h"
#include "snake.h"
// 表示互动物体的双向链表
typedef struct o_node {
	int x;
	int y;
	struct o_node* previous;
	struct o_node* next;
} O_Node;
typedef O_Node* PtrToNode;

typedef struct object {
	PtrToNode head;
	PtrToNode tail;
	int size;
	int parameters[2]; // 碰撞检测边界的参数，圆存放半径，矩形存放宽和高
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
status o_deleteOne(PtrToNode node, PtrToObject o);
status o_addObject(PtrToObject o); // 这里面包括各种物体的随机生成逻辑
void o_drawNode(PtrToNode node, int parameters[], Kind type); // 不同物体结点的统一绘制方法
void drawObject(PtrToObject o);
PtrToNode checkCollision(PtrToObject o, Snake snake);
status clearObject(PtrToObject o);
#endif // !_INTERACTIVE_OBJECTS_H
