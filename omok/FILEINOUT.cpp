#define _CRT_SECURE_NO_WARNINGS
#include "omok.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 500


void AIfileSave(char* name, Rank newone) {
	FILE* fp;
	fp = fopen(name, "w");
	
}

//오목판 결과 # 순위 # 이름 # 시간
Rank* RankfileLead(char* name, Rank* arr, int* n)
{
    FILE *fp;
    Rank *res, thng;
    char str[100], msg[50], board[100];
    strcpy(msg, "파일이 없습니다.\n");
    int count = 1;
    fp = fopen(name, "r");
    res = (Rank*)malloc(sizeof(Rank) * 3);
    if (fp == NULL) errors(msg);

    else if (fp != NULL) {
        while (fgets(str, MAX_CHAR_PER_LINE, fp)) {
            if ((*n % 3) == 0 && !(*n == 0)) {
                count += 1;
                realloc(res, sizeof(Rank) * (count * 3));
            }
            strcpy(board, strtok(str, "#"));
            
            *n = *n + 1;
        }
        fclose(fp);
    }

    return res;
} 