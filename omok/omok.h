#pragma once

//Ű���� ��ũ��
#define UP 72		//����Ű ��
#define DOWN 80		//����Ű �Ʒ�
#define LEFT 75		//����Ű ����
#define RIGHT 77	//����Ű ������
#define ENTER 13	//����Ű
#define ESC 27		//ESCŰ

//��� ��ũ��
#define BLACK 1
#define WHITE 2
#define EMPTY 0
#define DRAW_BLACK printf("��")
#define DRAW_WHITE printf("��")

//�ٵ��� ũ�� ���� ��ũ��
#define StartpointX 40
#define StartpointY 20
#define MAX_X 15
#define MAX_Y 15
#define EndpointX (StartpointX + (MAX_X - 1) * 2)
#define EndpointY (StartpointY + (MAX_Y - 1))

void errors(char* msg);

typedef struct _omokboard {
	int board[MAX_Y][MAX_X];
} Omokboard;

typedef struct _rank
{
	Omokboard* result;
	char name[20];
	char time[20];
} Rank;

typedef struct _record {
	Omokboard* result;
	int who;
	char name1[3];
	char name2[3];
} Record;

void title(void); // ����ȭ��

void putstone(Omokboard* play, int x, int y, int player);	//���͸� ������ �� ���� ��ġ ���
int checkcanstone(Omokboard* board, int x, int y, int direction);	//������ ���⿡�� ���� �� �ִ� ������ ��ġ������ �Ÿ� ��ȯ
void checkstartstone(Omokboard* play, int* x, int* y); // ���� ���� �� ���� ��Ȳ���� ���������� ���� ���� �� �ִ���, �� ���´ٸ� ��ü�� ���� �� ����
int checkGameStatus(int board[MAX_Y][MAX_X]);	//winlose
int turn(int board[MAX_Y][MAX_X], int depth, int* a, int* b, int evex, int evey); //AI ����
int getWeight(int board[MAX_Y][MAX_X], int x, int y);
bool isindexoutofboundsexception(int x, int y);

int minimax(int board[MAX_Y][MAX_X], int depth, int maximizingPlayer, int x, int y);