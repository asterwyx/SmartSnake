#ifndef _DEFINE_H
#define _DEFINE_H
// 刷新间隔
#define DELTA 32
// 游戏输赢状态
#define WIN 1
#define LOSE -1
#define CONTINUE 0
// 键值
#define LEFT 0x4B00
#define RIGHT 0x4D00
#define UP 0x4800
#define DOWN 0x5000
#define ESC 0x01
#define ENTER 0x1C0D
#define KEY_W 'W'
#define KEY_A 'A'
#define KEY_S 'S'
#define KEY_D 'D'
// 游戏初始值和默认值
#define STARTX 50 // 表示游戏区在屏幕上的起始X坐标
#define STARTY 50 // 表示游戏区在屏幕上的起始Y坐标
#define SIZEX 20 // 表示一个方块的长度
#define SIZEY 20 // 表示一个方块的宽度
#define SNAKE_NODE_SIZE 5
#define DEFAULT_MOVE_SPEED 5
#define SNAKE_MOVE_SPEED 2
#define INIT_SNAKE_X 200
#define INIT_SNAKE_Y 200
// 用来表示函数操作成功与否的返回状态
#define SUCCESS 0  // 沿用Unix方式，0为成功与真，非零数代表其他
#define FAILURE 1
#define ERROR -1
#define YES 0
#define NO 1
typedef int status;
#endif // !_DEFINE_H
