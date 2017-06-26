

#ifndef TOOLS_H_
#define TOOLS_H_

/** \typedef
 * coordinate per spostamento
 */
typedef struct coord{
	int x;
	int y;
}coord;

/** \typedef
 * coordinate degli elementi sul campo
 */
typedef struct positions{
	coord *xy;
	int npos;
}positions;

/** \typedef
 * array di stringhe
 */
typedef struct string{
	char string[100];
}string;

/** \typedef
 * array di stringhe
 */
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

/** \fn void  GotoXY(int , int  )

 * funzione che si sposta nelle coordinate stabilite
 */
void  GotoXY(int , int  );


/** \fn void getCursorXY(int *, int *)

 * funzione che sposta il cursore nelle coordinate stabilite
 */
void getCursorXY(int *, int *);

/** \fn void hidecursor()

 * funzione che cancella il cursore dalla schermata
 */
void hidecursor();


/** \fn int consoleTitle(char [])

 * funzione titolo della console
 */
int consoleTitle(char []);



/** \fn bool ListDirectoryContents( const char *, char [2048] )

 * funzione che cerca tutti i file che stanno nella cartella e li carica nella lista
 */
bool ListDirectoryContents( const char *, char [2048] );


/** \fn int getFileQuantity( char [], char [4]  )

 * funzione che conta conta quanti file ci sono nella lista
 */
int getFileQuantity( char [], char [4]  );


/** \fn int getFilePath(char dir[], char extension[4], string_arr *saves )

 * funzione che riempie l'array con i salvataggi
 */
int getFilePath(char dir[], char extension[4], string_arr *saves );
