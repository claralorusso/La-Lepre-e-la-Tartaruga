#ifndef GUI_H_
#define GUI_H_

#include <stdio.h>
#include "game.h"
#include "arrays.h"
#include "tools.h"

#define BG_WHITE "\x1b[47m"
#define BLACK  "\x1b[30m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYANO  "\x1B[36m"
#define WHITE  "\x1B[37m"


typedef struct movepos{
	positions *animals;
}movepos;

void printHand(array *);

void printBet(array *);

void printPlayed(array *);

void printTitle(void);

void printMenu(void);

void printRoute(void);

void printRef();

void printStatics();

void printStaticsSettings();

void printTurn(char [], bool);

void printPointer(int , bool );

void allocPositions();

void setPositions();

int printAnimal(int animal, int pos);

void playerErrors();

void drawSquare(coord angle1, coord angle2);

void printScore(players *, array *);

#endif /* GUI_H_ */
