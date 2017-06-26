#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include "game.h"
#include "arrays.h"
#include "tools.h"

/** \def  BG_WHITE "\x1b[47m"
 *  colore
 */
#define BG_WHITE "\x1b[47m"

/** \def  BLACK  "\x1b[30m"
 *  colore
 */
#define BLACK  "\x1b[30m"

/** \def  RED  "\x1B[31m"
 *  colore
 */
#define RED  "\x1B[31m"

/** \def  GREEN  "\x1B[32m"
 *  colore
 */
#define GREEN  "\x1B[32m"

/** \def  YELLOW  "\x1B[33m"
 *  colore
 */
#define YELLOW  "\x1B[33m"

/** \def   BLU  "\x1B[34m"
 *  colore
 */
#define BLU  "\x1B[34m"

/** \def  MAGENTA  "\x1B[35m"

 *  colore
 */
#define MAGENTA  "\x1B[35m"

/** \def  CYANO  "\x1B[36m"
 *  colore
 */
#define CYANO  "\x1B[36m"

/** \def  WHITE  "\x1B[37m"
 *  colore
 */
#define WHITE  "\x1B[37m"

/** \typedef
 * vettore che contiene posizioni degli animali
 */
typedef struct movepos{
	positions *animals;
}movepos;

/** \fn void printHand(array *)

 * funzione di stampa il vettore delle carte in mano
 */
void printHand(array *);


/** \fn void printBet(array *)

 * funzione di stampa carte scommessa
 */
void printBet(array *);


/** \fn void printPlayed(array *

 * funzione di stampa giocatore
 */
void printPlayed(array *);


/** \fn void printTitle(void)

 * funzione di stampa titolo
 */
void printTitle(void);


/** \fn void printMenu(void)

 * funzione di stampa menu
 */
void printMenu(void);


/** \fn printRoute(void)

 * funzione di stampa percorso
 */
void printRoute(void);


/** \fn void printRef()

 * funzione di stampa legenda
 */
void printRef();


/** \fn void printWinnerPos(array *winners)

 * funzione di stampa posizioni podio
 */
void printWinnerPos(array *winners);


/** \fn void printStatics()

 * funzione di stampa  comandi nel gioco
 */
void printStatics();


/** \fn void printStaticsRules()
 * funzione di stampa  comandi del gioco nelle regole
 */
void printStaticsRules();


/** \fn void printStaticsSettings()

 * funzione di stampa  comandi del gioco nelle impostazioni
 */
void printStaticsSettings();


/** \fn void printStaticsSaveGame()

 * funzione di stampa comandi nel salva partita
 */
void printStaticsSaveGame();


/** \fn void printStaticsLoadGame()

 * funzione di stampa comandi nel carica partita
 */
void printStaticsLoadGame();


/** \fn void printTurn(char [], bool)

 * funzione di stampa turno
 */
void printTurn(char [], bool);


/** \fn void printPointer(int , bool )

 * funzione di stampa puntatore che seleziona le carte
 */
void printPointer(int , bool );


/** \fn void allocPositions()

 * funzione di allocazione delle posizioni
 */
void allocPositions();


/** \fn void setPositions()

 * funzione che setta le posizioni degli animali nel percorso
 */
void setPositions();


/** \fn int printAnimal(int animal, int pos)

 * funzione di stampa animale
 */
int printAnimal(int animal, int pos);


/** \fn void playerErrors()

 * funzione di errore giocatore
 */
void playerErrors();


/** \fn void drawSquare(coord angle1, coord angle2

 * funzione che disegna un quadrilatero
 */
void drawSquare(coord angle1, coord angle2);


/** \fn void printScore(players *, array *)

 * funzione di stampa punteggio
 */
void printScore(players *, array *);

/** \fn int SelectorMovement(char input, coord start, int *option, int max, char);

 * funzione movimento dell'indicatore nel menu
 */
int SelectorMovement(char input, coord start, int *option, int max, char);

#endif /* GUI_H_ */
