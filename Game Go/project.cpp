#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
#include<stdlib.h>

const int uparrow = 0x48;//up arrow
const int leftarrow = 0x4b;//left arrow
const int rightarrow = 0x4d;//rigt arrow
const int downarrow = 0x50;//down arrow
const int boardpostionx = 50;//x postion of the board 
const int boardpostiony = 2;// y postion of the board
const int blackrock = 1;// black rock value
const int whiterock = 2;//white rock value
const int empty = 0;// value of empty crossing
const char wall = '#';// border symbol
const char emptysymbol = ' ';//empty symbol


void blackrocks(int x, int y);
void whiterocks(int x, int y);
void setbackgroundcolor();
void printboard(int** board, int xboard, int yboard, int size);
void printmenu(int menupostion, int xboard, int yboard, int blackpoints, int whitepoints);
void printcursor(int element, int x, int y);
void clearpostionbefore(int beforex, int beforey, int element);
int putRocks(int** board, int yboard, int xboard, int size, int rockvalue);
int beating(int** board, int yboard, int xboard, int size, int myvalue);
int obliczilemamoddechow(int** board, int yboard, int xboard, int size, int myvalue, bool** niepowtarzaj);
int kill(int** board, int yboard, int xboard, int size, int myvalue, bool** niepowtarzaj);
void wyczysc(bool** niepowtrzaj, int size);
int changesizeboard();
void savingfile(int** board, int size, int numerofmoves, int blackpoints, int whitepoints);
bool loadingfile(int**& board, int& size, int& numerofmoves, int& blackpoints, int& whitepoints);
bool enteresc();
bool suecide(int** board, int xboard, int yboard, int size, int rockvalue);
int main()
{
        while (true) {//Nowa gra
                int menuposition = 1;
                int size = changesizeboard();
                bool ishandicup = false;
                int numerofmoves = 0;
                int blackpoints = 0;
                int whitepoints = 6;
                int** board = new int* [size];
                for (int i = 0; i < size; i++)
                {
                        board[i] = new int[size];
                        for (int j = 0; j < size; j++)
                                board[i][j] = 0;
                }
                setbackgroundcolor();
                printboard(board, boardpostionx, boardpostiony, size);
                int playerInput = 0, x = boardpostionx, y = boardpostiony, textColor = LIGHTGRAY, back = BLACK;
                int beforex = x;
                int beforey = y;
                settitle("Krzysztof, Ostrzycki, 193507");
                _setcursortype(_NOCURSOR);
                do {// tura gracza
                        int xboard = x - boardpostionx;
                        int yboard = y - boardpostiony;
                        textcolor(LIGHTGRAY);
                        printmenu(menuposition, xboard, yboard, blackpoints, whitepoints);
                        clearpostionbefore(beforex, beforey, board[beforey - boardpostiony][beforex - boardpostionx]);
                        printcursor(board[yboard][xboard], x, y);
                        playerInput = getch();
                        if (playerInput == 0) {
                                beforex = x;
                                beforey = y;
                                playerInput = getch();          // the next code knowing that this
                                if (playerInput == (uparrow) && (y > boardpostiony)) y--;       // will be a special key
                                else if ((playerInput == downarrow) && (y < boardpostiony + size - 1)) y++;
                                else if ((playerInput == leftarrow) && (x > boardpostionx)) x--;
                                else if ((playerInput == rightarrow) && (x < boardpostionx + size - 1)) x++;
                        }
                        else if (playerInput == 'h' && numerofmoves == 0)
                        {
                                ishandicup = true;
                                whitepoints = 0;
                        }
                        else if (playerInput == 'g')
                        {
                                ishandicup = false;
                                numerofmoves += 1;
                        }
                        else if (playerInput == 'q')
                                return 0;
                        else if (playerInput == 'i')
                        {
                                int rockvalue;
                                if (numerofmoves % 2 == 0)
                                {
                                        rockvalue = blackrock;
                                        blackrocks(x, y);
                                }
                                else
                                {
                                        rockvalue = whiterock;
                                        whiterocks(x, y);
                                }
                                if (suecide(board, xboard, yboard, size, rockvalue) == true)
                                {
                                        textbackground(CYAN);
                                        continue;
                                }
                                if (enteresc() == false)
                                {
                                        textbackground(CYAN);
                                        putch(empty);
                                        continue;
                                }
                                if (ishandicup == true)
                                        numerofmoves += 1;
                                numerofmoves += 1;
                                int zabito = putRocks(board, yboard, xboard, size, rockvalue);
                                if (rockvalue == blackrock)
                                        blackpoints += zabito;
                                else
                                        whitepoints += zabito;
                        }
                        else if (playerInput == 's')
                                savingfile(board, size, numerofmoves, blackpoints, whitepoints);
                        else if (playerInput == 'l')
                        {
                                if (loadingfile(board, size, numerofmoves, blackpoints, whitepoints) == true)
                                {
                                        setbackgroundcolor();
                                        textcolor(LIGHTGRAY);
                                        clrscr();
                                        printboard(board, boardpostionx, boardpostiony, size);
                                }
                        }
                } while (playerInput != 'n');
                for (int k = 0; k < size; k++)
                {
                        delete[] board[k];
                }
                delete[]board;
                _setcursortype(_NORMALCURSOR);
        }
        return 0;
}
void blackrocks(int x, int y)//defines black rocks
{
        textcolor(BLACK);
        gotoxy(x, y);
        cputs("*");

}
void whiterocks(int x, int y)//defines white rocks
{
        textcolor(WHITE);
        gotoxy(x, y);
        cputs("*");

}
void setbackgroundcolor()//setting backgroud color
{
        textbackground(CYAN);
        clrscr();
}
void printboard(int** board, int xboard, int yboard, int size)//printing board
{

        for (int j = 0; j < size; j++)
        {

                for (int i = 0; i < size; i++)
                {
                        if (board[j][i] == empty)
                        {
                                gotoxy(xboard + i, yboard + j);
                                putch(emptysymbol);
                        }
                        else if (board[j][i] == blackrock)
                        {
                                blackrocks(i + xboard, j + yboard);
                        }
                        else if (board[j][i] == whiterock)
                        {
                                whiterocks(i + xboard, j + yboard);
                        }

                }

        }
        textcolor(WHITE);
        for (int k = 0; k < size + 2; k++)
        {
                gotoxy(xboard - 1, yboard - 1);
                putch(wall);
                yboard = yboard + 1;

        }
        for (int k = 0; k < size + 1; k++)
        {
                gotoxy(xboard, yboard - 2);
                putch(wall);
                xboard = xboard + 1;

        }
        for (int k = 0; k < size + 2; k++)
        {
                gotoxy(xboard - 1, yboard - 2);
                putch(wall);
                yboard = yboard - 1;

        }
        for (int k = 0; k < size + 1; k++)
        {
                gotoxy(xboard - 1, yboard - 1);
                putch(wall);
                xboard = xboard - 1;

        }

}
void printmenu(int menupostion, int xboard, int yboard, int blackpoints, int whitepoints)//printing menu
{
        textbackground(CYAN);
        char x[4] = "  ";
        char y[4] = "  ";
        int i = 2;
        do {
                x[i] = xboard % 10 + '0';
                xboard = xboard / 10;
                i--;

        } while (xboard > 0);
        i = 2;
        do {
                y[i] = yboard % 10 + '0';
                yboard = yboard / 10;
                i--;

        } while (yboard > 0);
        gotoxy(menupostion, 1);
        cputs("Krzysztof Ostrzycki 193507");
        gotoxy(menupostion, 2);
        cputs("arrows: moving the cursor over the board");
        gotoxy(menupostion, 3);
        cputs("s: save the game state");
        gotoxy(menupostion, 4);
        cputs("l: load the game state");
        gotoxy(menupostion, 5);
        cputs("n: new game");
        gotoxy(menupostion, 6);
        cputs("i: put the rock");
        gotoxy(menupostion, 7);
        cputs("current cursor postion x y: ");
        cputs(x);
        cputs(" ");
        cputs(y);
        gotoxy(menupostion, 8);
        cputs("enter: confirm choice and end players turn ");
        gotoxy(menupostion, 9);
        cputs("esc: cancel current action ");
        gotoxy(menupostion, 10);
        cputs("q: exit");
        gotoxy(menupostion, 11);
        cputs("blackpoints: ");
        putch(blackpoints + '0');
        gotoxy(menupostion, 12);
        cputs("white points: ");
        putch(whitepoints + '0');
        cputs(".5");
        gotoxy(menupostion, 13);
        cputs("h: handicap");
        gotoxy(menupostion, 14);
        cputs("g: stop handicap");
}
void printcursor(int element, int x, int y)//printing coursor
{
        textbackground(RED);
        if (element == empty)
        {
                gotoxy(x, y);
                putch(emptysymbol);
        }
        else if (element == blackrock)
        {
                blackrocks(x, y);
        }
        else if (element == whiterock)
        {
                whiterocks(x, y);
        }
}
void clearpostionbefore(int beforex, int beforey, int element)// clearing after cursor movement
{

        textbackground(CYAN);
        if (element == empty)
        {
                gotoxy(beforex, beforey);
                putch(emptysymbol);
        }
        else if (element == blackrock)
        {
                blackrocks(beforex, beforey);
        }
        else if (element == whiterock)
        {
                whiterocks(beforex, beforey);
        }
}
int putRocks(int** board, int yboard, int xboard, int size, int rockvalue)//function defined to put rocks
{
        if ((board[yboard][xboard] == empty) && (rockvalue == blackrock))
        {
                board[yboard][xboard] = blackrock;
                return beating(board, yboard, xboard, size, blackrock);
        }
        else if ((board[yboard][xboard] == empty) && (rockvalue == whiterock))
        {
                board[yboard][xboard] = whiterock;
                return beating(board, yboard, xboard, size, whiterock);

        }
}
int beating(int** board, int yboard, int xboard, int size, int myvalue)//conditions to kill

{
        int suma = 0;
        bool** niepowtarzaj = new bool* [size];
        for (int i = 0; i < size; i++)
        {
                niepowtarzaj[i] = new bool[size];
                for (int k = 0; k < size; k++)
                {
                        niepowtarzaj[i][k] = false;
                }
        }
        int enemyvalue = blackrock;
        if (myvalue == blackrock)
        {
                enemyvalue = whiterock;
        }
        //lewy
        if (xboard != 0 && board[yboard][xboard - 1] == enemyvalue)
        {
                if (obliczilemamoddechow(board, yboard, xboard - 1, size, enemyvalue, niepowtarzaj) == 0)
                {
                        suma += kill(board, yboard, xboard - 1, size, enemyvalue, niepowtarzaj);
                }
                wyczysc(niepowtarzaj, size);
        }

        //prawy
        if (xboard != size - 1 && board[yboard][xboard + 1] == enemyvalue)
        {
                if (obliczilemamoddechow(board, yboard, xboard + 1, size, enemyvalue, niepowtarzaj) == 0)
                {
                        suma += kill(board, yboard, xboard + 1, size, enemyvalue, niepowtarzaj);
                }
                wyczysc(niepowtarzaj, size);
        }

        //gora
        if (yboard != 0 && board[yboard - 1][xboard] == enemyvalue)
        {
                if (obliczilemamoddechow(board, yboard - 1, xboard, size, enemyvalue, niepowtarzaj) == 0)
                {
                        suma += kill(board, yboard - 1, xboard, size, enemyvalue, niepowtarzaj);

                }
                wyczysc(niepowtarzaj, size);
        }

        //dol
        if (yboard != size - 1 && board[yboard + 1][xboard] == enemyvalue)
        {
                if (obliczilemamoddechow(board, yboard + 1, xboard, size, enemyvalue, niepowtarzaj) == 0)
                {
                        suma += kill(board, yboard + 1, xboard, size, enemyvalue, niepowtarzaj);

                }
                wyczysc(niepowtarzaj, size);
        }
        for (int k = 0; k < size; k++)
        {
                delete[] niepowtarzaj[k];
        }
        delete[] niepowtarzaj;
        return suma;
}
int obliczilemamoddechow(int** board, int yboard, int xboard, int size, int myvalue, bool** niepowtarzaj)//counts how many breaths
{
        int liczbaoddechow = 4;
        if (xboard == 0 || board[yboard][xboard - 1] != empty)
        {
                liczbaoddechow--;
        }
        if (xboard == size - 1 || board[yboard][xboard + 1] != empty)
        {
                liczbaoddechow--;
        }
        if (yboard == 0 || board[yboard - 1][xboard] != empty)
        {
                liczbaoddechow--;
        }
        if (yboard == size - 1 || board[yboard + 1][xboard] != empty)
        {
                liczbaoddechow--;
        }

        niepowtarzaj[yboard][xboard] = true;

        if (xboard != 0 && board[yboard][xboard - 1] == myvalue && niepowtarzaj[yboard][xboard - 1] == false)
        {
                liczbaoddechow += obliczilemamoddechow(board, yboard, xboard - 1, size, myvalue, niepowtarzaj);
        }
        if (xboard != size - 1 && board[yboard][xboard + 1] == myvalue && niepowtarzaj[yboard][xboard + 1] == false)
        {
                liczbaoddechow += obliczilemamoddechow(board, yboard, xboard + 1, size, myvalue, niepowtarzaj);
        }
        if (yboard != 0 && board[yboard - 1][xboard] == myvalue && niepowtarzaj[yboard - 1][xboard] == false)
        {
                liczbaoddechow += obliczilemamoddechow(board, yboard - 1, xboard, size, myvalue, niepowtarzaj);
        }
        if (yboard != size - 1 && board[yboard + 1][xboard] == myvalue && niepowtarzaj[yboard + 1][xboard] == false)
        {
                liczbaoddechow += obliczilemamoddechow(board, yboard + 1, xboard, size, myvalue, niepowtarzaj);
        }
        return liczbaoddechow;

}
int kill(int** board, int yboard, int xboard, int size, int myvalue, bool** niepowtarzaj)//removes the killed stone and increases the score
{
        int suma = 0;
        for (int i = 0; i < size; i++)
        {
                for (int k = 0; k < size; k++)
                {
                        if (niepowtarzaj[i][k] == true)
                        {
                                board[i][k] = empty;
                                gotoxy(k + boardpostionx, i + boardpostiony);
                                textbackground(CYAN);
                                putch(emptysymbol);
                                suma++;
                        }
                }
        }
        return suma;
}
void wyczysc(bool** niepowtrzaj, int size)
{
        for (int i = 0; i < size; i++)
        {
                for (int k = 0; k < size; k++)
                {
                        niepowtrzaj[i][k] = false;
                }
        }
}
int changesizeboard()//change size of the board
{
        textcolor(LIGHTGRAY);
        textbackground(BLACK);
        setbackgroundcolor();
        clrscr();

        gotoxy(1, 1);
        cputs("Menu: ");
        gotoxy(1, 2);
        cputs("1: 9x9");
        gotoxy(1, 3);
        cputs("2: 13x13");
        gotoxy(1, 4);
        cputs("3: 19x19");
        gotoxy(1, 5);
        cputs("4: Choose your own size");
        char userInput = getche();
        if (userInput == '1')
        {
                return 9;
        }
        else if (userInput == '2')
        {
                return 13;
        }
        else if (userInput == '3')
        {
                return 19;
        }
        else if (userInput == '4')
        {
                char tab[4] = " ";
                int i = 0;
                clrscr();
                textcolor(LIGHTGRAY);
                textbackground(CYAN);
                gotoxy(1, 1);
                cputs("Write your size:");
                gotoxy(1, 2);
                do {
                        userInput = getche();
                        if (userInput != 0xd)
                        {
                                tab[i] = userInput;
                                i++;
                        }
                } while (userInput != 0xd);
                return atoi(tab);
        }
        return 9;


}
void savingfile(int** board, int size, int numerofmoves, int blackpoints, int whitepoints)//save file to load
{
        FILE* fp;
        fp = fopen("savefile.txt", "w");
        if (fp != NULL)
        {
                fwrite(&size, sizeof(size), 1, fp);
                fwrite(&blackpoints, sizeof(blackpoints), 1, fp);
                fwrite(&whitepoints, sizeof(whitepoints), 1, fp);
                fwrite(&numerofmoves, sizeof(numerofmoves), 1, fp);
                for (int i = 0; i < size; i++)
                {

                        for (int k = 0; k < size; k++)
                        {
                                fwrite(&board[i][k], sizeof(int), 1, fp);
                        }
                }
                fclose(fp);
        }
}
bool loadingfile(int**& board, int& size, int& numerofmoves, int& blackpoints, int& whitepoints)//load file
{
        FILE* fp;
        fp = fopen("savefile.txt", "r");
        if (fp != NULL)
        {
                for (int i = 0; i < size; i++)
                {
                        delete[]board[i];
                }
                delete[]board;

                fread(&size, sizeof(size), 1, fp);
                fread(&blackpoints, sizeof(blackpoints), 1, fp);
                fread(&whitepoints, sizeof(whitepoints), 1, fp);
                fread(&numerofmoves, sizeof(numerofmoves), 1, fp);
                board = new int* [size];

                for (int i = 0; i < size; i++)
                {
                        board[i] = new int[size];
                }

                for (int i = 0; i < size; i++)
                {
                        for (int k = 0; k < size; k++)
                        {
                                fread(&board[i][k], sizeof(int), 1, fp);
                        }
                }
                fclose(fp);
                return true;
        }
        return false;
}
bool enteresc()//enter and escape conditon
{
        char userInput = 0;
        while (userInput != 0x0d && userInput != 0x1b)
        {
                userInput = getch();
                if (userInput == 0x1b)
                {
                        return false;
                }
                if (userInput == 0x0d)
                {
                        return true;
                }

        }

}
bool suecide(int** board, int xboard, int yboard, int size, int rockvalue)//prevent from sueside
{
        int value = 0;
        if (xboard == 0 || board[yboard][xboard - 1] != empty && board[yboard][xboard - 1] != rockvalue)
        {
                value += 1;
        }
        if (xboard == size - 1 || board[yboard][xboard + 1] != empty && board[yboard][xboard + 1] != rockvalue)
        {
                value += 1;
        }
        if (yboard == 0 || board[yboard - 1][xboard] != empty && board[yboard - 1][xboard] != rockvalue)
        {
                value += 1;
        }
        if (yboard == size - 1 || board[yboard + 1][xboard] != empty && board[yboard + 1][xboard] != rockvalue)
        {
                value += 1;
        }
        if (value == 4)
        {
                return true;
        }
        return false;
}