#include<stdio.h>
#include<windows.h>
#include "SingleHangman.c"
#include "DoubleHangman.c"
#include "tictacsingle.c"
#include "tictacmulti.c"
#include <mmsystem.h>



void gotoxy1(int x,int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int main(){
    PlaySound(TEXT("Music.wav"), NULL, SND_FILENAME | SND_ASYNC);
    int choice, x;
    while(1){
    system("color 0a");
    system("cls");
    gotoxy1(73,2);
    printf("G A M E   A R C A D E");
    gotoxy1(73,5);
    printf("1   To Play Guess The Word");
    gotoxy1(73,6);
    printf("2   To Play Tic Tac Toe");
    gotoxy1(73,7);
    printf("0   To Exit");
    do{
    gotoxy1(73,8);
    scanf("%d",&choice);
    }while(choice!=0 && choice!=1 && choice!=2);
    switch(choice){
        case 1:
        system("cls");
        gotoxy1(73,2);
        printf("G U E S S   T H E   W O R D");
        gotoxy1(73,4);
        printf("1   To Play Single Player");
        gotoxy1(73,5);
        printf("2   To Play Multi Players");
        do{
        gotoxy1(73,6);
        scanf("%d",&x);
        }while(x!=1 && x!=2);
        PlaySound(NULL, NULL, SND_PURGE);
        if(x==1){
            singleplayer();
        }else twoplayer();
        break;
        case 2:
        system("cls");
        gotoxy1(73,2);
        printf("T I C   T A C   T O E");
        gotoxy1(73,4);
        printf("1   To Play Single Player");
        gotoxy1(73,5);
        printf("2   To Play Multi Players");
        do{
        gotoxy1(73,6);
        scanf("%d",&x);
        }while(x!=1 && x!=2);
        PlaySound(NULL, NULL, SND_PURGE);
        if(x==1){
            tictacsingle();
        }else tictacmulti();
        break;
    }
    if(choice==0){
        break;
        }
    }
}
