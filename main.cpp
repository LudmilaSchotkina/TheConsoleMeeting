#include <iostream>
#include "GameHeader.h"

using namespace std;

int main ()
{
    int i=1, j=1, counter=0;
    bool exit=0;
    int  M,  N;
    getFieldSize(M,N);

    char **field = new char *[M];
    for(int i=0; i<M; ++i)
        field[i] = new char[N];

    getField(field,M,N);
    field[i][j]='1';
    field[M-2][N-2]='2';
    welcome();

    while(!exit)
    {
        printRules();
        cout<<endl<<endl;
        output(field,M,N);
        cout<<endl<<"Number of moves: "<<counter<<endl;
        ++counter;
        moveCursor(field,i,j,M,N);

        exit=ifEnd(field,i,j,M,N);
        if(exit)
            cout<<endl<<"Great! You win!!!"<<endl;
        else clearScreen ();
    }

    for(int i=0; i<M; ++i)
        delete []field[i];
    delete []field;
    ifExit();

    return 0;
}
