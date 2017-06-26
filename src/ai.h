#ifndef IA_H_
#define IA_H_

#include "arrays.h"
#include "globals.h"


/** \typedef
 * vettore di pozioni dalle carte scelte
 * carta scelta
 */
typedef struct aiturn{
	array pos;
	int choice;
}aiturn;


/** \fn int ia2betcard(array *temp, int betcard)

 * funzione di scelta della seconda carta scommessa della i.a.
 */
int ia2betcard(array *temp, int betcard);


/** \fn int iamain(array *, array *, int , int )

 * funzione turno della i.a.
 */
int iamain(array *, array *, int , int );

/** \fn int check(aiturn *, array *)

 * funzione controlla che si giochi almeno una carta
 */
int check(aiturn *, array *);


/** \fn int final_check(aiturn *, array *, array *, int )

 * funzione controlla che s
 */


#endif /* IA_H_ */

