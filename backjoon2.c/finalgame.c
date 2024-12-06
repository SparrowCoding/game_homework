#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>//오직 강제종료 exit를 위해서 라이브러리 삽입

#define WIDTH 30
#define HEIGHT 38 
#define CLS system("cls")
#define MAX_RANK 5

//textcolor 함수 숫자를 통해 색을 넣을수있다.
void textcolor(int Num) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Num);//색을 고르게 해주는 포인터
}

//목숨이랑 스코어는 전역변수로 선언
int mogsuk = 3;
int score = 0;

typedef struct {
    char name[30];
    int score;
} Player;

Player rankingList[MAX_RANK] = { //랭킹에 아무도 없으면 구분이 안된다고 생각해서 넣는 리스트
    {"제작자의 최대 점수", 8684},
    {"강한수염", 94},
    {"둘명박", 80},
    {"언철수", 70},
    {"곰재인", 60}
};
void update(const char* name, int score) {//const char 문자열 포인터, char* 과 다르게 const char*는 문자열 상수를 가르키지만 대신에 다른값을 덮을수 없다.
    Player newPlayer;
    strcpy(newPlayer.name, name); // 입력된 이름을 새 플레이어 구조체에 복사하는 코드
    newPlayer.score = score;      

    rankingList[MAX_RANK - 1] = newPlayer;

    // 랭킹을 점수 기준으로 그시기 정렬하는 코드
    for (int i = MAX_RANK - 1; i > 0; i--) {
        
        if (rankingList[i].score > rankingList[i - 1].score) {
            Player temp = rankingList[i];       
            rankingList[i] = rankingList[i - 1]; 
            rankingList[i - 1] = temp;          
        }
        else {
            break;//아닐시 브릭
        }
    }
}

void removeCursor(void) {//게임할때 거슬리는 커서 지우는 코드.
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
    textcolor(7);
    for (int i = 0; i < MAX_RANK; i++) {
        gotoxy(15, 22 + i);
        printf("%d등    %s   %d점", i + 1, rankingList[i].name, rankingList[i].score);
        //ranking 리스트에서 불러와서 순서대로 나열하기
    }
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
    gotoxy(40, 14);
    printf("도움말: wasd로 *를 움직입니다.");
    gotoxy(30, 20);
    printf("w: 위로 이동, a: 왼쪽 이동, s: 아래로 이동, d: 오른쪽 이동 q: 메뉴로 돌아가기 단 게임 점수는 저장안됨");
    gotoxy(40, 23);
    printf("q: 메뉴로 돌아가기 단 게임 점수는 저장안됨, l: 자살하는 키 (랭킹에 점수 저장 가능)");
    gotoxy(45, 26);
    printf("메뉴로 돌아가려면 아무 키나 누르세요...");
    getch();//아무키나 입력하면 넘어가지는 코드.
    CLS;
}
void StartMenu() {
    SetConsoleTitle(TEXT("brick pihagi"));// cmd창 이름 바꾸는 명령어 window.h 기능 중에 하나
    CLS;
    int choice = 1;
    char input;

    while (1) {
        CLS;
        gotoxy(10, 2);
        textcolor(7);
        printf("■■ 시작하기 전에 최대화 버튼을 눌러 콘솔창을 제일 크게 만들어 주십시오. ■■");
        gotoxy(10, 3);
        printf("한국어로 설정되어있으면 게임과 움직이지 않습니다. W와 S로 커서를 움직이고 엔터로 원하는 설정에 들어가세요");
        gotoxy(30, 5);
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
        if (input == 'w' || input == 'W') { //w랑 대문자 W를 다르게 인식하므로 둘다 || or로 인식하게 하였다.
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
                gamemainLoop();
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
                exit(0);
                
            }
        }
    }
}


void drawWall(int wallX, int wallY) {
    gotoxy(wallX, wallY);
    printf("\033[0;31m###\033[0;31m");
}

void death(int score) {
    CLS;
    gotoxy(30, 15);
    printf("게임 오버!");
    gotoxy(30, 16);
    textcolor(7);
    printf(" * 랭킹에 당신의 점수가 기재 됩니다 * ");
    gotoxy(30, 17);
    printf("당신의 점수는 %d점 입니다.", score);
    gotoxy(30, 19);
    char name[30];
    printf("이름을 입력해주세요: ");  scanf("%s", name);
    update(name, score);
 
    score = 0;
    mogsuk = 3;
    StartMenu();
}
void check(int playerX, int playerY, int wallX, int wallY) {
    
    if (playerX >= wallX && playerX < wallX + 3 && playerY == wallY) {
        mogsuk--;
        if (mogsuk <= 0) {
            death(score);
           
        }
    }
}
int gamemainLoop() {
    CLS;
    srand(time(NULL)); 
    char xy = 0;
    int x = 15, y = 30; 
    int prevX = x, prevY = y;
    int wallX[5]; 
    int wallY[5] = { 1, 1, 1, 1, 1 };
    score = 0;     // 게임 시작 시 점수 초기화해야하므로 넣음
    mogsuk = 3;
    
    for (int i = 0; i < 5; i++) {
        wallX[i] = rand() % (WIDTH - 3) + 1;
    }

    while (1) {
        CLS;  

        for (int i = 0; i < 5; i++) {
            drawWall(wallX[i], wallY[i]);
            wallY[i]++;  

            if (wallY[i] >= HEIGHT) {
                wallY[i] = 1;
                wallX[i] = rand() % (WIDTH - 3) + 1;  
            }
            check(x, y, wallX[i], wallY[i]);
            score++;
        }

        gotoxy(prevX, prevY);
        printf(" ");

        gotoxy(x, y);
        printf("\033[0;33m*\033[0;33m");

        
        gotoxy(0, HEIGHT);
        printf("\033[0;37m점수: %d\033[0;37m", score);
        gotoxy(26, HEIGHT);
        printf("\033[0;37m목숨:\033[0;37m");
        for (int i = 0; i < mogsuk; i++) {
            printf("\033[0;32m$\033[0;32m");
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
            case 'q':
                StartMenu();//저장 안됨
            case 'l':
                death(score);
            case 'p'://제작자 치트키
                mogsuk = 30;
            }

        }
        Sleep(8);  
    }

  
}


int main() {
    removeCursor();
    StartMenu();
    return 0;
}
