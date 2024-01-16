#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

char board[9];
const char PLAYER='X';
const char COMPUTER='O';

void resetBoard1()
{
    for(int i=0;i<9;i++)
    {
        board[i]=' ';
    }
}
void printBoard1()
{
    system("cls");
    printf(" %c | %c | %c ", board[0], board[1], board[2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[3], board[4], board[5]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[6], board[7], board[8]);
    printf("\n");
}
int checkFreeSpaces1()
{
    int freeSpaces=9;
    for(int i=0;i<9;i++)
    {
        if(board[i]!=' ')
        {
            freeSpaces--;
        }
    }
    return freeSpaces;
}
void playerMove1()
{
    int x;
    printf("Enter Choice:");
    scanf("%d", &x);
    x--;
    if(board[x]!=' ')
    {
        system("cls");
        printBoard1();
        printf("Invalid Move\n");
        PlaySound(TEXT("Incorrect.wav"), NULL, SND_FILENAME | SND_ASYNC);
        playerMove1();
    }
    else
    {
        board[x]=PLAYER;
        PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}

void printWinner1(char winner)
{
    if(winner==PLAYER)
    {
        printf("YOU WON!");
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if(winner==COMPUTER)
    {
        printf("YOU LOSE!");
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else
    {
        printf("IT'S A TIE!");
        PlaySound(TEXT("Gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}
void computerMove()
{
    int x;
    srand(time(0));
    if(checkFreeSpaces1()>0)
    {  
        do
        {
            x=rand()%9;
        }while(board[x]!=' ');
        board[x]=COMPUTER;
    }
    else
    {
        printWinner1(' ');
    }
}

// char checkWinner()
// {
//     //Checking Rows
//     for(int i=0;i<9;i=i+3)
//     {
//         if(board[i]==board[i+1] && board[i]==board[i+2])
//         {
//             return board[i];
//         }
//     }
//     //Checking Columns
//     for(int i=0;i<3;i++)
//     {
//         if(board[i]==board[i+3] && board[i]==board[i+6])
//         {
//             return board[i];
//         }
//     }
//     //Checking first Diagonal
//     if(board[0]==board[4] && board[0]==board[8])
//     {
//         return board[0];
//     }
//     //Checking second Diagonal
//     if(board[2]==board[4] && board[2]==board[6])
//     {
//         return board[2];
//     }
//     return ' ';
// }
char checkWinner1()
{
    //Checking Rows
    for(int i=0;i<3;i++)
    {
        if(board[i*3]==board[(i*3)+1] && board[i*3]==board[(i*3)+2] && board[i*3]!=' ')
        {
            return board[i*3];
        }
    }
    //Checking Columns
    for(int i=0;i<3;i++)
    {
        if(board[i]==board[i+3] && board[i]==board[i+6] && board[i]!=' ')
        {
            return board[i];
        }
    }
    //Checking first Diagonal
    if(board[0]==board[4] && board[0]==board[8] && board[0]!=' ')
    {
        return board[0];
    }
    //Checking second Diagonal
    if(board[2]==board[4] && board[2]==board[6] && board[2]!=' ')
    {
        return board[2];
    }
    return ' ';
}

int tictacsingle()
{
    char winner=' ';
    resetBoard1();
    char input;
    do
    {
        char winner=' ';
        resetBoard1();
        while(winner==' ' && checkFreeSpaces1()!=0)
    {
        printBoard1();
        playerMove1();
        winner=checkWinner1();
        if(winner!=' ' || checkFreeSpaces1()==0)
        {
            break;
        }

        printBoard1();
        computerMove();
        winner=checkWinner1();
        if(winner!=' ' || checkFreeSpaces1()==0)
        {
            break;
        }
    }
    printBoard1();
    printWinner1(winner);
    printf("\nDo you want to play again(Y/N):");
    input=getche();
    } while (input=='Y' || input=='y');
    return 0;
}