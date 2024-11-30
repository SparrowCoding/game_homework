#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 30
#define HEIGHT 38 
#define UX 30 
#define UY 45
#define UZ 45
#define CLS system("cls")


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

void gotoxy(int x, int y) { // *를 움직이게 해주는 gotoxy 함수
    COORD pos = { x, y }; // COORD 구조체
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos); // * 를 움직이게 해주는 핸들.
}
void ranking() {
    CLS;
    gotoxy(2, 1);
    printf("\n=========================랭킹============================\n");
    printf("");


    printf("\n=========================================================\n");
    getch();
    CLS;
}
void gamestart() {
    CLS;
    printf("게임을 시작합니다...\n");
    Sleep(1000);
    CLS;
}

void help() {
    CLS;

    printf("도움말: 방향키로 *를 움직입니다.\n");
    printf("w: 위로 이동, a: 왼쪽 이동, s: 아래로 이동, d: 오른쪽 이동\n");
    printf("메뉴로 돌아가려면 아무 키나 누르세요...\n");
    getch();
    CLS;
}
void map() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT -1|| j == 0 || j == WIDTH-1) {
                printf("ㅁ");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void death() {
    CLS;
    gotoxy(30, 30);
    printf("게임 오버!\n");
    printf("이름을 입력해주세요 : "); 

    getch();
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
    int mogsuk = 3;
    int score = 0;

    char screenBuffer[HEIGHT][WIDTH]; 

    removeCursor();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                screenBuffer[i][j] = '#'; 
            }
            else {
                screenBuffer[i][j] = ' '; 
            }
        }
    }

    while (1) {
        
        screenBuffer[y][x] = '*';

       
        CLS;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                printf("%c", screenBuffer[i][j]);
            }
            printf("\n");
        }

       
        gotoxy(0, HEIGHT);
        printf("점수: %d    목숨: ", score);
        for (int i = 0; i < mogsuk; i++) {
            printf("$");
        }

        
        screenBuffer[y][x] = ' ';

        if (mogsuk == 0) {
            death();
            break;
        }

        
        if (_kbhit()) {
            xy = _getch();
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


void enemy(int x, int y) {
    gotoxy(0,0);

}

void StartMenu() {
    int choice;

    while (1) {
        system("mode con:cols=1000 lines=10");
        printf("시작하기전에 최대화 버튼을 눌러 콘솔창을 제일 크게 만들어 주십시오.\n");
        printf("===== 게임 메뉴 =====\n");
        gotoxy(50, -20);
        printf("1. 게임 시작\n");
        gotoxy(50, 30);
        printf("2. 도움말\n");
        printf("3. 랭킹 확인하기\n");
        printf("9. 종료\n");
        printf("=====================\n");
        printf("번호를 입력하시오: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            gamestart();
            gameLoop();
            break;

        case 2:
            help();
            break;

        case 9:
            printf("게임을 종료합니다.\n");
            return;
        case 3:
            ranking();
            break;

        case 1119:
            break;

        default:
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
            Sleep(1000);
            system("cls");
            break;

        }
    }
}

int main() {

    StartMenu();
    return 0;
}

//메인에서 스타트 누르면 호출 탈출할수있는 기능 넣기 
// 다시 메인으로 돌아갈수있게 제작하기
// 메인으로 뭔가 키로 받아서 점수 보기