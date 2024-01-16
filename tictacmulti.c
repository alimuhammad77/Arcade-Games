#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

char board[9];
const char PLAYER1='X';
const char PLAYER2='O';

void resetBoard()
{
    for(int i=0;i<9;i++)
    {
        board[i]=' ';
    }
}
void printBoard()
{
    system("cls");
    printf(" %c | %c | %c ", board[0], board[1], board[2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[3], board[4], board[5]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[6], board[7], board[8]);
    printf("\n");
}
int checkFreeSpaces()
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
void player1Move()
{
    int x;
    printf("Enter Choice:");
    scanf("%d", &x);
    x--;
    if(board[x]!= ' ')
    {
        system("cls");
        printBoard();
        printf("Invalid Move\n");
        PlaySound(TEXT("Incorrect.wav"), NULL, SND_FILENAME | SND_ASYNC);
        player1Move();
    }
    else
    {
        board[x]=PLAYER1;
        PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}
void printWinner(char winner)
{
    if(winner==PLAYER1)
    {
        printf("Player 1 won");
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else if(winner==PLAYER2)
    {
        printf("Player2 won");
        PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else
    {
        printf("IT'S A TIE!");
        PlaySound(TEXT("Gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}
void player2Move()
{
    int x;
    printf("Enter Choice:");
    scanf("%d", &x);
    x--;
    if(board[x]!= ' ')
    {  
        system("cls");
        printBoard();
        printf("Invalid Move\n");
        PlaySound(TEXT("Incorrect.wav"), NULL, SND_FILENAME | SND_ASYNC);
        player2Move();
    }
    else
    {
        board[x]=PLAYER2;
        PlaySound(TEXT("Correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
char checkWinner()
{
    //Checking Rows
    for (int i = 0; i < 3; ++i)
    {
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3] == board[i * 3 + 2] && board[i * 3] != ' ')
        {
            return board[i * 3];
        }
    }
    //Checking Columns
    for (int i = 0; i < 3; ++i)
    {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
        {
            return board[i];
        }
    }
    //Checking first Diagonal
    if (board[0] == board[4] && board[0] == board[8] && board[0] != ' ')
    {
        return board[0];
    }
    //Checking second Diagonal
    if (board[2] == board[4] && board[2] == board[6] && board[2] != ' ')
    {
        return board[2];
    }
    return ' ';
}


int tictacmulti()
{
    char winner=' ';
    resetBoard();
    char input;
    do
    {
        char winner=' ';
        resetBoard();
        while(winner==' ' && checkFreeSpaces()!=0)
    {
        printBoard();
        player1Move();
        winner=checkWinner();
        if(winner!=' ' || checkFreeSpaces()==0)
        {
            break;
        }

        printBoard();
        player2Move();
        winner=checkWinner();
        if(winner!=' ' || checkFreeSpaces()==0)
        {
            break;
        }
    }
    printBoard();
    printWinner(winner);
    printf("\nDo you want to play again(Y/N):");
    input=getche();
    } while (input=='Y' || input=='y');
    
    return 0;
}