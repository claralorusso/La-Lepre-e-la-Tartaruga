#ifndef GUI_H_
#define GUI_H_

#include "arrays.h"
#include "tools.h"

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
