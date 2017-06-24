

#ifndef TOOLS_H_
#define TOOLS_H_

typedef struct coord{
	int x;
	int y;
}coord;

typedef struct positions{
	coord *xy;
	int npos;
}positions;

typedef struct string{
	char string[100];
}string;

typedef struct string_arr{
	string *s;
	int n_string;
}string_arr;

/** \typedef \enum boolean
 *	Crea il tipo di dati per la lista eunumerata bool
 *
 */
typedef enum bool{false = 0, true = 1} bool;

#endif /* TOOLS_H_ */


void  GotoXY(int , int  );

void getCursorXY(int *, int *);

void hidecursor();

int consoleTitle(char []);

bool ListDirectoryContents( const char *, char [2048] );

int getFileQuantity( char [], char [4]  );

int getFilePath(char dir[], char extension[4], string_arr *saves );
