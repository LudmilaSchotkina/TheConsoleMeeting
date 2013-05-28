#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include<fstream>
#include <cstdlib>
#include "GameHeader.h"

using namespace std;

void welcome()
{
    cout<<endl<<"*********************************************************";
    cout<<endl<<"*\t\t\t\t\t\t\t*";
    cout<<endl<<"*  \t Let's play the game ConsoleMeeting!!! \t \t"<<"*";
    cout<<endl<<"*\t\t\t\t\t\t\t*";
    cout<<endl<<"*********************************************************";
    cout<<endl<<endl<<"...Press any key..."<<endl;
    getch();
    clearScreen ();
}

void printRules()
{
    char rule;
    ifstream in("rules.txt");
    if(!in)
    {
        cerr<<("Can't open file ")<<"rules.txt";
        exit(1);
    }
    while (!in.eof())
    {
        in.get(rule);
        cout<<rule;
    }
    in.close();
}

void getFieldSize(int &M,int &N)
{
    ifstream in("field.txt");
    if(!in)
    {
        cerr<<("Can't open file ")<<"field.txt";
        exit(1);
    }
    in>>M;
    in>>N;
}

void getField(char **field,int M,int N)
{
    char symbol;
    int a,b;
    ifstream in("field.txt");

    if(!in)
    {
        cerr<<("Can't open file ")<<"field.txt";
        exit(1);
    }
    in>>a;
    in>>b;
    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            in>>symbol;
            if(symbol=='1') symbol='#';
            if(symbol=='0') symbol=' ';

            field[i][j]=symbol;
        }
    }
    in.close();
}

void moveCursor(char **field, int &row, int &col, int  M, int N)
{
    char key=getch();
    switch(key)
    {
    case 'w':
    case 'W':
        if ((field[row-1][col]==' ')&&(field[M-row][N-1-col]==' '))
        {
            field[row-1][col]='1';
            field[row][col]=' ';
            field[M-row][N-1-col]='2';
            field[M-1-row][N-1-col]=' ';
            --row;
        }
        break;

    case 'a':
    case 'A':
        if ((field[row][col-1]==' ')&&(field[M-1-row][N-col]==' '))
        {
            field[row][col-1]='1';
            field[row][col]=' ';
            field[M-1-row][N-col]='2';
            field[M-1-row][N-1-col]=' ';
            --col;
        }
        break;

    case 's':
    case 'S':

        if ((field[row+1][col]==' ')&&(field[M-2-row][N-1-col]==' '))
        {
            field[row+1][col]='1';
            field[row][col]=' ';
            field[M-2-row][N-1-col]='2';
            field[M-1-row][N-1-col]=' ';
            ++row;
        }
        break;

    case 'd':
    case 'D':
        if ((field[row][col+1]==' ')&&(field[M-1-row][N-2-col]==' '))
        {
            field[row][col+1]='1';
            field[row][col]=' ';
            field[M-1-row][N-2-col]='2';
            field[M-1-row][N-1-col]=' ';
            ++col;
        }
        break;
    case 'q':
    case 'Q':
        cout<<"Bye bye!"<<endl;
        exit(0);
        break;
    }
}



bool ifEnd (char **field,int &row, int &col, int  M, int N)
{
    return (row==M-1-row&&row==M/2)&&(col==N-1-col&&col==N/2);
}

void ifExit()
{
    char key=getch();
    if (key=='q')
        exit(0);
}

void output(char **field, int  M, int N)
{
    for(int i = 0; i<M; ++i)
    {
        for(int j=0; j< N; ++j)
        {
            cout<<field[i][j];
        }
        cout<<endl;
    }
}

void clearScreen ()
{
    system("clear");
}

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


