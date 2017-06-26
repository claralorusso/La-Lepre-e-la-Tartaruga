
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "tools.h"
#include "globals.h"

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

bool ListDirectoryContents(const char *directory, char list[])
{
    WIN32_FIND_DATA file;
    HANDLE handle = NULL;
    char paths[2048];

    ///Specifica i fle. *.* = tutto
    sprintf(paths, "%s\\*.*", directory);

    if((handle = FindFirstFile(paths, &file)) == INVALID_HANDLE_VALUE)
    {

        ///printf("Percorso non trovato: [%s]\n", directory);
        return false;
    }

    do{

        if(strcmp(file.cFileName, ".") != 0
                && strcmp(file.cFileName, "..") != 0){

           /// Costruisce la lista utilizzando il nome del file
            sprintf(paths, "%s\\%s\n", directory, file.cFileName);

            /// L'entit� � un file o una cartella?
            if(file.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {    /// controlla che non sia una cartella

            } else {
            	/// Stampa a video
            	///printf("File: %s\n", paths);
            	strncat(list, paths, strlen(paths) );
            }

        }
    }while(FindNextFile(handle, &file)); ///cerca il prossimo file.

    FindClose(handle);

    return true;
}

int getFileQuantity(char dir[], char extension[4])
{
	char save_list[10000];
	char c;

	int i;
	int count;
	if ( ListDirectoryContents(dir, save_list) == false ) return FAILURE;

	count = 0;
	i = 0;
	while ( i < strlen(save_list) ){

		c = save_list[i];
		/// trova la fine riga
		if ( c == '\n' ){
			/// controlla che il file sia il file cercato
			if ( save_list[i - 4] == extension[0] && save_list[i - 3] == extension[1] && save_list[i - 2] == extension[2] && save_list[i - 1] == extension[3] ){
				count++;
			}
		}
		i++;
	}
	strcpy(save_list,"");
	return count;
}


int getFilePath(char dir[], char extension[4], string_arr *saves  )
{
	char save_list[10000];
	char c, x;
	int i, j, sFound;
	int save_len;

	if (ListDirectoryContents(dir, save_list) == false) return FAILURE;

	saves->n_string = getFileQuantity(dir, extension);
	saves->s = malloc(saves->n_string * sizeof( string ) );

	sFound = 0;
	i = 0;
	while ( i < strlen(save_list) ){

		c = save_list[i];
		/// trova la fine riga
		if ( c == '\n' ){
			/// controlla che il file sia il file cercato
			if ( save_list[i - 4] == extension[0] && save_list[i - 3] == extension[1] && save_list[i - 2] == extension[2] && save_list[i - 1] == extension[3] ){

				save_len = 0;
				j = i - 1;
				while ( (x = save_list[j]) != '\\' ){

					save_len++;
					j--;
				}
				strncpy( saves->s[sFound].string, save_list + i - save_len , save_len);
				saves->s[sFound].string[save_len] = '\0';

				sFound++;
			}

		}
		i++;
	}

	strcpy(save_list,"");

	return sFound;
}
