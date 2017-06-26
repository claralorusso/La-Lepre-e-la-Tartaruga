#ifndef IA_H_
#define IA_H_

#include "arrays.h"
#include "globals.h"

typedef struct aiturn{
	array pos;
	int choice;
}aiturn;


int ia2betcard(array *temp, int betcard);

int iamain(array *, array *, int , int );

int check(aiturn *, array *);

int final_check(aiturn *, array *, array *, int );

#endif /* IA_H_ */

