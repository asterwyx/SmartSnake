#ifndef _DEFINE_H
#define _DEFINE_H
// ˢ�¼��
#define DELTA 32
// ��Ϸ��Ӯ״̬
#define WIN 1
#define LOSE -1
#define CONTINUE 0
// ��ֵ
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
// ��Ϸ��ʼֵ��Ĭ��ֵ
#define STARTX 50 // ��ʾ��Ϸ������Ļ�ϵ���ʼX����
#define STARTY 50 // ��ʾ��Ϸ������Ļ�ϵ���ʼY����
#define SIZEX 20 // ��ʾһ������ĳ���
#define SIZEY 20 // ��ʾһ������Ŀ��
#define MINE_NODE_SIZE 7
#define SNAKE_NODE_SIZE 5
#define FOOD_NODE_WIDTH 1
#define FOOD_NODE_HEIGHT 1
#define GRASS_NODE_WIDTH 1
#define GRASS_NODE_HEIGHT 1
#define WALL_NODE_WIDTH 1
#define WALL_NODE_HEIGHT 1
#define DEFAULT_MOVE_SPEED 5
#define SNAKE_MOVE_SPEED 2
#define INIT_SNAKE_X 200
#define INIT_SNAKE_Y 200
#define MAP_WIDTH 1000
#define MAP_HEIGHT 700
#define WINDOW_WIDTH MAP_WIDTH + 200
#define WINDOW_HEIGHT MAP_HEIGHT
#define INIT_XDIRECTION 1
#define INIT_YDIRECTION 0
// ������ʾ���������ɹ����ķ���״̬
#define SUCCESS 0  // ����Unix��ʽ��0Ϊ�ɹ����棬��������������
#define FAILURE 1
#define ERROR -1
#define YES 0
#define NO 1

// ��������ĵ÷֣���ը��ը������ֱ�Ӽ��룬����ζ��Խ������ը����ʧԽ��
#define FOOD_SCORE 10
#define POISON_SCORE -16
#define WISDOM_SCORE 18

// �����������ɫ
#define SNAKE_COLOR RGB(0, 0, 255)
#define MINE_COLOR RGB(12, 12, 12)
#define FOOD_COLOR RGB(127, 127, 0)
#define POISON_COLOR RGB(255, 0, 0)
#define WISDOM_GRASS_COLOR RGB(0, 255, 0)
#define WALL_COLOR RGB(255, 127, 0)
// ��Ϸ�Ѷ�����
#define DEFAULT_FOOD_NUMBER 4
#define DEFAULT_MINE_NUMBER 5
#define DEFAULT_POISON_NUMBER 15
#define DEFAULT_WISDOM_NUMBER 2
#define DEFAULT_WALL_NUMBER 10
#define POISON_EXIST_TIME 1000
typedef int status;
typedef enum level {
	EASY,
	MEDIUM,
	HARD
} Level;

typedef enum kind
{
	FOOD,
	MINE,
	POISONOUSWEEDS,
	WISDOMGRASS,
	WALL
} Kind;
// ���ߺ���
extern double dist(int x1, int y1, int x2, int y2);

#endif // !_DEFINE_H
