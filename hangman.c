#include <stdio.h> 
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <ctype.h>

void color(int x){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,x);
}

void gotoxy(int x,int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void textcolor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,color);
}
void gameName(){
    gotoxy(73,2);
    color(2);
    printf("G U E S S    T H E    W O R D\n");
}
void user(char user[2][20]){
    system("cls");
    gameName();
    color(2);
    gotoxy(70,4);
    printf("Enter The Name Of User 1: ");
    scanf(" %19s", user[0]);
    gotoxy(70,5);
    printf("Enter The Name Of User 2: ");
    scanf(" %19s", user[1]);
}
void input(char word[20],char hint[20],int *life,char answer[20],char user[2][20],int ran){
    int i=0;
    system("cls");
    gameName();
    gotoxy(72,4);
    color(2);
    printf("%s Enter The Word: ",user[ran]);
    gotoxy(100,4);
    for (i = 0; i < 20; i++) {
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
    gotoxy(72,5);
    printf("Enter A Hint: ");
    scanf("%19s",hint);
    if(strlen(word)<=10){
        *life=4;
    }else *life=6;
}
void graphics(char word[20],int *life,char answer[20],char users[2][20],int *ran,char hint[20]){
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    char uScore=22,heart=3;
    system("cls");
    gameName();
    color(2);
    for(int i=0;i<strlen(word)*2;i++){
        gotoxy(75+(2*i),5);
        if(isalpha(word[i]))
        printf("%c",uScore);
        else if(word[i]=='-'){
            gotoxy(75+(2*i),4);
            printf("-");
        }else printf(" ");
    }
    color(4);
    for(int i=0;i<*life;i++){
        gotoxy(55+(2*i),2);
        printf("%c ",heart);
    }
    gotoxy(115,2);
    printf("Currently Guessing:%s",users[(*ran+1)%2]);
    gotoxy(115,3);
    printf("Hint:%s",hint);
    color(2);
}
void music(char path[50]){
        char openCommand[100];
        sprintf(openCommand, "open \"%s\" type waveaudio alias audio", path);
        mciSendString(openCommand, NULL, 0, NULL);
        mciSendString("play audio", NULL, 0, NULL);
        Sleep(800);
        if(strcmp(path,"Gameover.wav")==0 || strcmp(path,"Victory.wav")==0){
            Sleep(2000);
        }
        if(strcmp(path,"GameSound.wav")!=0){
        mciSendString("close audio", NULL, 0, NULL);
        }
    }

void game(char word[20],char answer[20],int *life){
    int flag=0;
    static int i=0;
    char input;
    gotoxy(53,5);
    printf("Input Character: ");
    input=getch();
    printf("%c",input);
    printf("\b ");
    for(int i=0;i<strlen(word);i++){
        if(tolower(word[i]) == tolower(input)){
            flag=1;
            gotoxy(75,7);
            printf("You Have Guessed Correctly!  ");
            char path[50]={"Correct.wav"};
            music(path);
            answer[i]=input;
            gotoxy(75+(i*2),4);
            printf("%c",toupper(answer[i]));
        }
    }
    if(flag==0){
        (*life)--;
        for(int i=3;i>=*life;i--){
            gotoxy(55+(2*i),2);
            printf(" ");
            gotoxy(75,7);
            printf("You Have Guessed Incorrectly!");
        }
        char path[50]={"Incorrect.wav"};
        music(path);
}
}

int gameEnd(char word[20],int *life,char answer[20],char user[2][20],int *ran,int *choice1){
    int allGuessed=1;
    for (int i = 0; i < strlen(word); i++) {
        if (tolower(answer[i]) != tolower(word[i])) {
            allGuessed = 0;
            break;
        }
    }
    if((*life)==0){
        system("cls");
        gotoxy(75,3);
        printf("%s Won The Game",user[*ran]);
        gotoxy(75,4);
        printf("%s Guessed Incorrectly!!\n",user[(*ran+1)%2]);
        gotoxy(75,5);
        printf("0   Exit ");
        gotoxy(75,6);
        printf("1   Play Again\n");
        gotoxy(75,7);
        char path[50]="Gameover.wav";
        music(path);
        *ran= (*ran+1)%2;
        scanf("%d",&*choice1);
    }else if(*life>0 && allGuessed){
        system("cls");
        gotoxy(75,3);
        printf("%s Has Won The Game!!\n",user[(*ran+1)%2]);
        gotoxy(75,4);
        printf("0   Exit");
        gotoxy(75,5);
        printf("1   Play Again\n");
        gotoxy(75,6);
        *ran= (*ran+1)%2;
        char path[50]="Victory.wav";
        music(path);
        scanf("%d",&*choice1);
    }
       
}
void resetArrays(char word[20],char answer[20],char hint[20],int *life){
    for(int i=0;i<20;i++){
        word[i]=0;
        answer[i]=0;
        hint[i]=0;
        *life=0;
    }
}



int main(){
    //gcc test.c -o test.exe -lwinmm
    char word[20],hint[20],answer[20],users[2][20],gameMusic[50]="GameSound.wav";
    int life,choice=2;
    resetArrays(word,answer,hint,&life);
    user(users);
    srand(time(NULL));
    int ran=0;
    ran=rand()%2;
    input(word,hint,&life,answer,users,ran);
    graphics(word,&life,answer,users,&ran,hint);
    while(1){
        srand(time(NULL));
        if(choice==1){
        resetArrays(word,answer,hint,&life);
        input(word,hint,&life,answer,users,ran);
        graphics(word,&life,answer,users,&ran,hint);
        choice=2;
        }
        game(word,answer,&life);
        gameEnd(word,&life,answer,users,&ran,&choice);
        if(choice==0){
            break;
        }

    }
    system("cls");
    gotoxy(75,4);
    printf("Thanks For Playing");  
}