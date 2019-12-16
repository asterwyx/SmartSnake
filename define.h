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
#define SNAKE_NODE_SIZE 5
#define DEFAULT_MOVE_SPEED 5
#define SNAKE_MOVE_SPEED 2
#define INIT_SNAKE_X 200
#define INIT_SNAKE_Y 200
// ������ʾ���������ɹ����ķ���״̬
#define SUCCESS 0  // ����Unix��ʽ��0Ϊ�ɹ����棬��������������
#define FAILURE 1
#define ERROR -1
#define YES 0
#define NO 1
typedef int status;
#endif // !_DEFINE_H
