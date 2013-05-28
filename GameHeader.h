#ifndef GAMEHEADER_H
#define GAMEHEADER_H


void welcome();
void printRules();
void getFieldSize(int &M,int &N);
void getField(char **field,int M,int N);

void moveCursor(char **field, int &row, int &col, int  M, int N);
bool ifEnd (char **field,int &row, int &col, int  M, int N);
void ifExit();
void output(char **field, int  M, int N);
void clearScreen ();

int kbhit();
int getch();

#endif
