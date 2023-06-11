
#include "omok.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define MAX_CHAR_PER_LINE 1000

Record gameRecords[100]; // 기록을 저장할 구조체 배열
int numRecords = 0; // 저장된 기록의 개수

Record* loadResultFromFile(Record *records, int *recordIndex) {
    int count = 1;
    FILE* file = fopen("record.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return 0;
    }
    records = (Record*)malloc(sizeof(Record) * 100);
    *recordIndex = 0;
    int lineIndex = 0;
    char line[1000];

    while (fgets(line, MAX_CHAR_PER_LINE, file)) {

        //sscanf(line, "승패: %d", &(records[recordIndex].who));
        records[*recordIndex].who = atoi(strtok(line, "#"));

        //sscanf(line, "사용자 1P: %s", records[recordIndex].name1);
        strcpy(records[*recordIndex].name1, strtok(NULL, "#"));

        //sscanf(line, "사용자 2P: %s", records[recordIndex].name2);
        strcpy(records[*recordIndex].name2, strtok(NULL, "#"));

        for (int i = 0; i < MAX_Y; i++) {
            for (int j = 0; j < MAX_X; j++) {
                //sscanf(line, "%d", &(records[recordIndex].result.board[lineIndex - 4][i]));
                records[*recordIndex].result.board[i][j] = atoi(strtok(NULL, " "));
            }
        }
        printf("%d %d %s %s\n", *recordIndex, records[*recordIndex].who, records[*recordIndex].name1, records[*recordIndex].name2);
        for (int i = 0; i < MAX_Y; i++) {
            for (int j = 0; j < MAX_X; j++) {
                printf("%d ", records[*recordIndex].result.board[i][j]);
            }
            printf("\n");
        }

        *recordIndex = *recordIndex + 1;
    }

    fclose(file);
    return records;
}

void saveResultToFile(Record records[], int numRecords) {
    //numRecords = loadResultFromFile(gameRecords);
    FILE* file = fopen("record.txt", "a");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }

    for (int i = 0; i < numRecords; i++) {
        // 승패 정보 출력
        fprintf(file, "%d#", records[i].who);
        fflush(stdin);

        // 사용자 1P 이름 출력
        fprintf(file, "%s#", records[i].name1);
        fflush(stdin);

        // 사용자 2P 이름 출력
        fprintf(file, "%s#", records[i].name2);

        // 오목판 결과 출력
        for (int j = 0; j < MAX_Y; j++) {
            for (int k = 0; k < MAX_X; k++) {
                fprintf(file, "%d ", records[i].result.board[j][k]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

//오목판 결과 # 이름 # 시간
Rank* RankfileLead(Rank* arr, int* n)
{
    FILE *fp;
    Rank thng;
    char str[1000], msg[50], board[1000];
    char time[50];
    strcpy(msg, "파일이 없습니다.\n");
    int count = 1;
    fp = fopen("rank.txt", "r");
    arr = (Rank*)malloc(sizeof(Rank) * 100);
    if (fp == NULL) errors(msg);

    else if (fp != NULL) {
        while (fgets(str, MAX_CHAR_PER_LINE, fp)) {
            strcpy(board, strtok(str, "#"));

            strcpy(thng.name, strtok(NULL, "#"));
            strcpy(time, strtok(NULL, "#"));
            thng.time = atof(time);
            thng.result.board[0][0] = atoi(strtok(board, " "));
            for (int j = 1; j < MAX_X; j++) {
                thng.result.board[0][j] = atoi(strtok(NULL, " "));
            }
            for (int i = 1; i < MAX_Y; i++) {
                for (int j = 0; j < MAX_X; j++) {
                    thng.result.board[i][j] = atoi(strtok(NULL, " "));
                }
            }

            arr[*n] = thng;
            *n = *n + 1;
        }
        fclose(fp);
    }
    return arr;
} 

void RankfileSave(Rank newone) {
    FILE* fp;

    fp = fopen("rank.txt", "a");    //파일 쓰기 모드로 open

    char Result[1000], playername[10], time[50];
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            fprintf(fp, "%d ", newone.result.board[i][j]);
        }
    }
    fprintf(fp, "#");
    strcpy(playername, newone.name);
    sprintf(time, "%lf", newone.time);
    if (fp != NULL) {
        fprintf(fp, "%s#%s\n", playername, time);   //파일에 입력
    }
    fclose(fp); //파일 닫기
}