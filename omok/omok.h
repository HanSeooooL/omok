#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
//키보드 매크로
#define UP 72		//방향키 위
#define DOWN 80		//방향키 아래
#define LEFT 75		//방향키 왼쪽
#define RIGHT 77	//방향키 오른쪽
#define ENTER 13	//엔터키
#define ESC 27		//ESCZl

//흑백 매크로
#define BLACK 1
#define WHITE 2
#define EMPTY 0
#define DRAW_BLACK printf("○")
#define DRAW_WHITE printf("●")

//바둑판 크기 관련 매크로
#define StartpointX 30
#define StartpointY 10
#define MAX_X 15
#define MAX_Y 15
#define EndpointX (StartpointX + (MAX_X - 1) * 2)
#define EndpointY (StartpointY + (MAX_Y - 1))

void errors(char* msg);

typedef struct _omokboard {	//오목판 구조체
	int board[MAX_Y][MAX_X];
} Omokboard;

typedef struct _rank	//AI모드 기록 저장 구조체
{
	Omokboard result;
	char name[20];
	double time;
} Rank;

typedef struct _record {	//사용자대전기록 저장 구조체
	Omokboard result;
	int who;
	char name1[10];
	char name2[10];
} Record;

void title(void); // 메인화면

void putstone(Omokboard* play, int x, int y, int player);	//엔터를 눌렀을 때 돌의 위치 기록
int checkcanstone(Omokboard* board, int x, int y, int direction);	//지정한 방향에서 놓을 수 있는 최초의 위치까지의 거리 반환
void checkstartstone(Omokboard* play, int* x, int* y); // 돌을 놓은 후 다음 상황에서 시작지점에 돌을 놓을 수 있는지, 못 놓는다면 대체로 놓을 곳 선정
int checkGameStatus(int board[MAX_Y][MAX_X]);	//winlose 체크
int turn(int board[MAX_Y][MAX_X], int depth, int evex, int evey); //AI 메인(minmax)
int getWeight(int board[MAX_Y][MAX_X], int x, int y);	//AI 가중치 판별함수
bool isindexoutofboundsexception(int x, int y);	//AI에서 오목판 밖으로 나가는지 체크
int compare(const void* a, const void* b);	//qsort 비교함수

void saveResultToFile(Record records[], int numRecords);	//사용자대전 파일 저장
Record* loadResultFromFile(Record* records, int *recordIndex);	//사용자대전 파일 불러오기
void RankfileSave(Rank newone);	//AI모드 기록 파일저장
Rank* RankfileLead(Rank* arr, int* n);	//AI모드 기록 파일 불러오기