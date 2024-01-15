#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <ctype.h>


void music(char path[20]);
void color(int x);
void gotoxy(int x, int y);
void selectWord(char word[20], char hint[10]);
void gamestart(char user[20], char word[20], char hint[10]);
void reset(char word[20], char hint[10], int *life, bool alphabetsUsed[26], int *coord);
void gamerun(char user[20], char word[20], char hint[10], int *flag1, int *turn);

void color(int x) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void selectWord(char word[20], char hint[10]) {
    FILE *file1, *file2;
    file1 = fopen("Words.txt", "r");
    file2 = fopen("Hint.txt", "r");

    if (file1 == NULL || file2 == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int line;
    do {
        line = rand() % 284;
    } while (line == 0);

    bool trackline = true;
    int current_line = 1;

    while (fgets(word, 20, file1) != NULL && fgets(hint, 10, file2) != NULL) {
        if (line == current_line) {
            trackline = false;
            break;
        }
        current_line++;
    }

    fclose(file1);
    fclose(file2);

    word[strlen(word) - 1] = '\0';
}

void gamestart(char user[20], char word[20], char hint[10]) {
    system("cls");
    gotoxy(55, 2);
    printf("G U E S S   T H E   W O R D");

    for (int i = 0; i < strlen(word); i++) {
        gotoxy(56 + (2 * i), 5);
        printf("%c", 22);
    }

    color(4);
    gotoxy(100, 2);
    printf("User:%s", user);
    gotoxy(100, 3);
    printf("Hint:%s", hint);
    color(2);
}

void reset(char word[20], char hint[10], int *life, bool alphabetsUsed[26], int *coord) {
    *life = 5;
    *coord = 0;

    for (int i = 0; i < 26; i++) {
        word[i] = '\0';
        hint[i] = '\0';
        alphabetsUsed[i] = false;
    }
}

void gamerun(char user[20], char word[20], char hint[10], int *flag1, int *turn) {
    static bool alphabetsUsed[26] = {false};
    bool flag = false;
    static int life = 5;
    char input;
    char answer[20];
    bool allGuessed = true;

    gotoxy(56, 8);
    printf("                                                           ");
    gotoxy(35, 2);
    printf("           ");
    for (int i = 0; i < life; i++) {
        color(4);
        gotoxy(35 + (2 * i), 2);
        printf("%c", 3);
    }
    color(2);
    static int randhint=0;
    if(randhint==0){
    for(int i=0;i<2;i++){
        int k=rand()%strlen(word);
        answer[k]=word[k];
        alphabetsUsed[toupper(answer[k]) - 'A'] = true;
        for (int j=0;j<strlen(word);j++){
        if(toupper(answer[j])==toupper(word[j])){
            gotoxy(56+(2*j),4);
            printf("%c",toupper(answer[j]));
            }
        }
    }
    randhint=1;
    }
    do{
    gotoxy(35,5);
    printf("Input Character: ");
    input=getch();
    fflush(stdin);
    printf("%c\b ", toupper(input));
    }while(!isalpha(input));

    for (int i = 0; i < strlen(word); i++) {
        if (toupper(word[i]) == toupper(input)) {
            flag = true;
            gotoxy(56 + (2 * i), 4);
            printf("%c", toupper(word[i]));
            answer[i] = input;
        }
    }

    for (int i = 0; i < strlen(word); i++) {
        if (tolower(answer[i]) != tolower(word[i])) {
            allGuessed = false;
            break;
        }
    }

    static int coord = 0;

    if (alphabetsUsed[toupper(input) - 'A']) {
        printf("\x1b[%d;%df%c Is Used  ", 8, 56, toupper(input));
        PlaySound(TEXT("Incorrect.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else if (flag) {
        printf("\x1b[%d;%dfCorrect!!  ", 8, 56);
        PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        printf("\x1b[%d;%dfIncorrect!!  ", 8, 56);
        PlaySound(TEXT("Incorrect.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gotoxy(100, 4);
        printf("Wrong Guesses:");
        gotoxy(115 + (2 * coord), 4);
        printf("%c", toupper(input));
        coord++;
        life--;
    }

    alphabetsUsed[toupper(input) - 'A'] = true;
    Sleep(1000);
    if (life == 0) {
        system("cls");
        gotoxy(54, 4);
        printf("%s Has Lost!", user);
        gotoxy(54, 5);
        printf("Word:%s", word);
        PlaySound(TEXT("Gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gotoxy(54, 6);
        printf("1   To Play Again");
        gotoxy(54, 7);
        printf("0   To Exit");

        do {
            fflush(stdin);
            gotoxy(54, 8);
            scanf("%d", flag1);
        } while (*flag1 != 0 && *flag1 != 1);

        if (*flag1 == 1) {
            randhint=0;
            reset(word, hint, &life, alphabetsUsed, &coord);
            (*turn)++;
        }
    } else if (allGuessed) {
        system("cls");
        gotoxy(54, 4);
        printf("%s Won Lost!", user);
        gotoxy(54, 5);
        printf("Word:%s", word);
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gotoxy(54, 6);
        printf("1   To Play Again");
        gotoxy(54, 7);
        printf("0   To Exit");

        do {
            fflush(stdin);
            gotoxy(54, 8);
            scanf("%d", flag1);
        } while (*flag1 != 0 && *flag1 != 1);

        if (*flag1 == 1) {
            randhint=0;
            reset(word, hint, &life, alphabetsUsed, &coord);
            (*turn)++;
        }
    }
}

int main() {
    char user[20], word[20], hint[10];

    system("color 0a");
    system("cls");
    srand(time(NULL));

    gotoxy(55, 2);
    printf("G U E S S   T H E   W O R D");
    gotoxy(55, 5);
    printf("Enter Your Username: ");
    scanf("%19s", user);

    selectWord(word, hint);
    gamestart(user, word, hint);

    int flag = 1;
    int turn = 0;

    while (flag) {
        if (turn == 1) {
            selectWord(word, hint);
            gamestart(user, word, hint);
            turn = 0;
        }

        gamerun(user, word, hint, &flag, &turn);
    }

    return 0;
}