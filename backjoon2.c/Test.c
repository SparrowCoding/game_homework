#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "change.h"

#define WIDTH 30
#define HEIGHT 38 
#define UX 30 
#define UY 45
#define UZ 45
#define CLS system("cls")

int activeBuffer = 0;
void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

int score = 0;
typedef struct total
{
    char name[30];
    int totalPoint;
    int totalTime;
    char totalname;
};
void removeCursor(void) {
    CONSOLE_CURSOR_INFO cursor;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    GetConsoleCursorInfo(handle, &cursor);
    cursor.bVisible = 0;
    SetConsoleCursorInfo(handle, &cursor);
}

void gotoxy(int x, int y) { 
    COORD pos = { x, y }; // COORD 구조체
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos); // * 를 움직이게 해주는 핸들.
}
void gamestart() {
    CLS;
    printf("게임을 시작합니다...\n");
    Sleep(1000);
    CLS;
}
void ranking() {
    CLS;
    textcolor(6);
    gotoxy(30, 5); printf("    | 트로피 |");
    gotoxy(30, 6); printf("    \\       /");
    gotoxy(30, 7); printf("     \\_____/ ");
    gotoxy(30, 8); printf("       ||");
    gotoxy(30, 9); printf("       ||");
    gotoxy(30, 10); printf("       ||");
    gotoxy(30, 11); printf("       ||");
    gotoxy(30, 12); printf("       ||");
    gotoxy(30, 13); printf("       ||");
    gotoxy(30, 14); printf("    w__||__w");


    textcolor(6);
    gotoxy(10, 15);
    printf("=========================================================");
    gotoxy(30, 16);
    printf("       랭킹 시스템       ");
    gotoxy(10, 17);
    printf("=========================================================");

    gotoxy(15, 19);
    printf("등수\t이름\t\t점수");
    gotoxy(15, 20);
    printf("---------------------------------------------");

    textcolor(14);
    gotoxy(15, 22);
    printf("1등\t홍길동\t\t100점");

    textcolor(8);
    gotoxy(15, 23);
    printf("2등\t김철수\t\t90점");

    textcolor(11);
    gotoxy(15, 24);
    printf("3등\t이영희\t\t80점");

    textcolor(7);
    gotoxy(15, 25);
    printf("4등\t최민호\t\t70점");

    gotoxy(15, 26);
    printf("5등\t박지수\t\t60점");

    textcolor(6);
    gotoxy(10, 28);
    printf("=========================================================");
    gotoxy(15, 30);
    printf("메뉴로 돌아가려면 아무 키나 누르세요...");

    getch();
    textcolor(7);
    CLS;
}
void help() {
    CLS;

    printf("도움말: wasd로 *를 움직입니다.\n");
    printf("w: 위로 이동, a: 왼쪽 이동, s: 아래로 이동, d: 오른쪽 이동\n");
    printf("메뉴로 돌아가려면 아무 키나 누르세요...\n");
    getch();
    CLS;
}
void StartMenu() {
    CLS;
    int choice = 1;
    char input;

    while (1) {
        CLS;
        gotoxy(10, 2);
        textcolor(7);
        printf("■■ 시작하기 전에 최대화 버튼을 눌러 콘솔창을 제일 크게 만들어 주십시오. ■■");
        gotoxy(30, 4);
        textcolor(9);
        printf("===== 게임 메뉴 =====");

        for (int i = 1; i <= 4; i++) {
            gotoxy(30, 5 + i * 2);
            if (choice == i) {
                textcolor(10);
                printf(">> ");
            }
            else {
                textcolor(7);
                printf("   ");
            }

            switch (i) {
            case 1:
                printf("게임 시작");
                break;
            case 2:
                printf("도움말");
                break;
            case 3:
                printf("랭킹 확인하기");
                break;
            case 4:
                printf("종료");
                break;
            }
        }

        gotoxy(30, 14);
        textcolor(7);
        printf("=====================");

        input = _getch();
        if (input == 'w' || input == 'W') {
            if (choice > 1) {
                choice--;
            }
        }
        else if (input == 's' || input == 'S') {
            if (choice < 4) {
                choice++;
            }
        }
        else if (input == '\r') {
            switch (choice) {
            case 1:
                gamestart();
                gameLoop();
                break;
            case 2:
                help();
                break;
            case 3:
                ranking();
                break;
            case 4:
                textcolor(7);
                printf("게임을 종료합니다.\n");
                return;
            }
        }
    }
}







void enemy(int x, int y) {
    printf("==================");
    gotoxy(0, 0);

}

void death(int score) {
    CLS;
    gotoxy(30, 15);
    printf("게임 오버!");
    gotoxy(30, 17);
    printf("당신의 점수는 %d점 입니다.", score);
    gotoxy(30, 19);
    printf("이름을 입력해주세요: ");

    char playerName[30];
    scanf("%s", playerName);

    gotoxy(30, 21);
    printf("메뉴로 돌아가려면 아무 키나 누르세요...");
    getch();

    CLS;
    StartMenu(); // 메인 메뉴로 돌아가기
}
void space(int score, int mogsuk) {
    gotoxy(45, 0);
    printf("점수: %d", score);
    gotoxy(15, 0);
    printf("목숨: ");
    for (int i = 0; i < mogsuk; i++) {
        printf("$");
    }
}
void gameLoop() {
    char xy = 0;
    int x = 10, y = 10;
    int prevX = x, prevY = y;
    int mogsuk = 3;
    int score = 0;

    char screenBuffer[HEIGHT][WIDTH];

    removeCursor();


    while (1) {
        
        gotoxy(prevX, prevY);
        printf(" ");

        
        gotoxy(x, y);
        printf("*");

        
        gotoxy(0, HEIGHT);
        printf("점수: %d    목숨: ", score);
        for (int i = 0; i < mogsuk; i++) {
            
            printf("♥️");
        }

        if (mogsuk == 0) {
            break;
            death(score);
            break;
        }

        
        if (_kbhit()) {
            xy = _getch();
            prevX = x;
            prevY = y;

            switch (xy) {
            case 'w':
                if (y > 1) y--;
                break;
            case 'a':
                if (x > 1) x--;
                break;
            case 's':
                if (y < HEIGHT - 2) y++;
                break;
            case 'd':
                if (x < WIDTH - 2) x++;
                break;
            }
        }

        Sleep(50);
    }
}





int main() {
    removeCursor();
    StartMenu();
    return 0;
}

//메인에서 스타트 누르면 호출 탈출할수있는 기능 넣기 
// 다시 메인으로 돌아갈수있게 제작하기
// 메인으로 뭔가 키로 받아서 점수 보기