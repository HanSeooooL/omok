#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
//Ű���� ��ũ��
#define UP 72		//����Ű ��
#define DOWN 80		//����Ű �Ʒ�
#define LEFT 75		//����Ű ����
#define RIGHT 77	//����Ű ������
#define ENTER 13	//����Ű
#define ESC 27		//ESCZl

//��� ��ũ��
#define BLACK 1
#define WHITE 2
#define EMPTY 0
#define DRAW_BLACK printf("��")
#define DRAW_WHITE printf("��")

//�ٵ��� ũ�� ���� ��ũ��
#define StartpointX 30
#define StartpointY 10
#define MAX_X 15
#define MAX_Y 15
#define EndpointX (StartpointX + (MAX_X - 1) * 2)
#define EndpointY (StartpointY + (MAX_Y - 1))

void errors(char* msg);

typedef struct _omokboard {	//������ ����ü
	int board[MAX_Y][MAX_X];
} Omokboard;

typedef struct _rank	//AI��� ��� ���� ����ü
{
	Omokboard result;
	char name[20];
	double time;
} Rank;

typedef struct _record {	//����ڴ������ ���� ����ü
	Omokboard result;
	int who;
	char name1[10];
	char name2[10];
} Record;

void title(void); // ����ȭ��

void putstone(Omokboard* play, int x, int y, int player);	//���͸� ������ �� ���� ��ġ ���
int checkcanstone(Omokboard* board, int x, int y, int direction);	//������ ���⿡�� ���� �� �ִ� ������ ��ġ������ �Ÿ� ��ȯ
void checkstartstone(Omokboard* play, int* x, int* y); // ���� ���� �� ���� ��Ȳ���� ���������� ���� ���� �� �ִ���, �� ���´ٸ� ��ü�� ���� �� ����
int checkGameStatus(int board[MAX_Y][MAX_X]);	//winlose üũ
int turn(int board[MAX_Y][MAX_X], int depth, int evex, int evey); //AI ����(minmax)
int getWeight(int board[MAX_Y][MAX_X], int x, int y);	//AI ����ġ �Ǻ��Լ�
bool isindexoutofboundsexception(int x, int y);	//AI���� ������ ������ �������� üũ
int compare(const void* a, const void* b);	//qsort ���Լ�

void saveResultToFile(Record records[], int numRecords);	//����ڴ��� ���� ����
Record* loadResultFromFile(Record* records, int *recordIndex);	//����ڴ��� ���� �ҷ�����
void RankfileSave(Rank newone);	//AI��� ��� ��������
Rank* RankfileLead(Rank* arr, int* n);	//AI��� ��� ���� �ҷ�����