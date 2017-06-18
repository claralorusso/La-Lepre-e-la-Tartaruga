#ifndef GUI_H_
#define GUI_H_

#include "arrays.h"
#include "tools.h"
#include <stdio.h>

#define KNRM  "\x1B[0m"
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

void printTurn(char []);

void printPointer(int , bool );

void allocPositions(movepos *set);

void setPositions(movepos *set);

int printAnimal(int animal, int pos);

void playerErrors();

#endif /* GUI_H_ */
