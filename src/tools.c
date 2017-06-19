#include "tools.h"
#include <windows.h>



void  GotoXY(int x, int  y)
{

	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
}


void getCursorXY(int *x, int *y)
{

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if( GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi) ) {

        *x = csbi.dwCursorPosition.X;

        *y = csbi.dwCursorPosition.Y;

    }

}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int consoleTitle(char title[])
{
	if ( !SetConsoleTitle( title ) ){
			return 1;
	}

	return 0;
}


