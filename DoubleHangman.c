#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>

int turn=0;
bool alphabetsUsed[26]={false};
int coord = 0;


void gotoxy2(int x,int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void color1(int x){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,x);
}

void user(char user[2][20]){
    system("cls");
    gotoxy2(73,2);
    printf("G U E S S    T H E    W O R D\n");
    gotoxy2(70,4);
    printf("Enter The Name Of User 1: ");
    scanf(" %19s", user[0]);
    gotoxy2(70,5);
    printf("Enter The Name Of User 2: ");
    scanf(" %19s", user[1]);
}

void userInput(char user[2][20], char word[20], char hint[10]){
    system("cls");
    gotoxy2(73,2);
    printf("G U E S S    T H E    W O R D\n");
    gotoxy2(72,4);
    printf("%s Enter A Word: ",user[turn]);
    gotoxy2(99,4);
    for (int i = 0; i < 20; i++) {
        word[i] = getch();
        if(word[i]==8){
            if (i>0) {
                i-=2;
                printf("\b \b");
            }else{
                i--;
            }
        }else if(!isalpha(word[i]) && word[i] != '-' && word[i] != 13) {
            word[i] = '\0';
            i--;
            continue;
        } else 
            printf("*");
        if (word[i]==13){
            word[i] = '\0';
            printf("\b ");
            break;
        }
    }
    gotoxy2(72,5);
    printf("Enter A Hint: ");
    scanf("%19s",hint);
    turn=(turn+1)%2;
}

void display(char user[2][20],char word[20],char hint[10], int *life,int score[2]){
    system("cls");
    gotoxy2(73,2);
    printf("G U E S S    T H E    W O R D\n");
    for(int i=0;i<strlen(word);i++){
        gotoxy2(75+(2*i),5);
        printf("%c",22);
    }
    color1(4);
    for(int i=0;i<*life;i++){
        gotoxy2(55+(2*i),2);
        printf("%c ",3);
    }
    gotoxy2(115,2);
    printf("Currently Guessing:%s",user[turn]);
    gotoxy2(115,3);
    printf("Hint:%s",hint);
    gotoxy2(115,5);
    printf("%s: %d",user[0],score[0]);
    gotoxy2(115,6);
    printf("%s: %d",user[1],score[1]);
    color1(2);
    gotoxy2(53,5);
    printf("Input Character: ");
}
void resetArrays(char word[20],char hint[10], char answer[20],int *life, bool alphabetsUsed[26]){
    for(int i=0;i<26;i++){
        word[i]='\0';
        hint[i]='\0';
        answer[i]='\0';
        alphabetsUsed[i]=false;
    }
    *life=5;
    coord=0;
}

void takeInput(char word[20],int *life,char answer[20]){
    int input;
    gotoxy2(75,7);
    printf("                                     ");
    do{
    gotoxy2(69,5);
    input=getch();
    printf("%c",input);
    printf("\b ");
    }while(!isalpha(input));
    int flag=0;
    for (int i = 0; i < strlen(word); i++) {
        if (toupper(word[i]) == toupper(input)) {
            flag = 1;
            gotoxy2(75 + (2 * i), 4);
            printf("%c", toupper(word[i]));
            answer[i] = input;
        }
    }
    if (alphabetsUsed[toupper(input) - 'A']) {
        gotoxy2(75,7);
        printf("%c Is Used",toupper(input));
        PlaySound(TEXT("Bruh.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else if (flag) {
        gotoxy2(75,7);
        printf("Correct!!");
        PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        gotoxy2(75,7);
        printf("Incorrect!!");
        PlaySound(TEXT("Incorrect.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gotoxy2(115, 7);
        printf("Wrong Guesses:");
        gotoxy2(130 + (2 * coord), 7);
        printf("%c", toupper(input));
        coord++;
        (*life)--;
        gotoxy2(65-(2*coord),2);
        printf(" ");
    }
    alphabetsUsed[toupper(input) - 'A'] = true;
    Sleep(1000);
}

void gameEnd(char word[20],char answer[20],int *life,int *choice,char user[2][20],int score[2]){
    int allGuessed=1;
    for(int i=0;i<strlen(word);i++){
        if(toupper(word[i])!=toupper(answer[i])){
            allGuessed=0;
        }
    }
    if (*life == 0) {
        system("cls");
        gotoxy2(70, 4);
        printf("%s Has Lost!", user[turn]);
        gotoxy2(70, 5);
        printf("Word:%s", word);
        PlaySound(TEXT("Gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gotoxy2(70, 6);
        printf("1   To Play Again");
        gotoxy2(70, 7);
        printf("0   To Go Back To Main Menu");
        do{
        gotoxy2(70, 8);
        scanf("%d",choice);
        }while(*choice!=0 && *choice!=1);
        score[(turn+1)%2]++;
    } else if (allGuessed) {
        system("cls");
        gotoxy2(70, 4);
        printf("%s Has Won!", user[turn]);
        gotoxy2(70, 5);
        printf("Word:%s", word);
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
        gotoxy2(70, 6);
        printf("1   To Play Again");
        gotoxy2(70, 7);
        printf("0   To Go Back To Main Menu");
        do{
        gotoxy2(70, 8);
        scanf("%d",choice);
        }while(*choice!=0 && *choice!=1);
        score[turn]++;
    }
}

int twoplayer(){
    char username[2][20],word[20],hint[10],answer[20];
    int life=5,score[2]={0,0};
    system("color 0a");
    user(username);
    userInput(username,word,hint);
    display(username,word,hint,&life,score);
    int choice=2;
    do{
        if(choice==1){
        resetArrays(word,hint,answer,&life,alphabetsUsed);
        userInput(username,word,hint);
        display(username,word,hint,&life,score);
        choice=2;
        }
        takeInput(word,&life,answer);
        gameEnd(word,answer,&life,&choice,username,score);
    }while(choice!=0);
    system("cls");
    gotoxy2(70, 4);
    if (score[0] > score[1]) {
    printf("%s Won The Game", username[0]);
    }else if (score[1] > score[0]){
    printf("%s Won The Game", username[1]);
    }else{
    printf("The Game is a Tie");
    }
    PlaySound(TEXT("GameEnd.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
}