#ifndef ARRAYS_H_
#define ARRAYS_H_
#include "tools.h"

/** \typedef
 * vettore di interi
 */
typedef struct array{
	int *d;
	int n;
}array;


/** \fn array arrInit(array *, int)
 * funzione che inizializza il vettore
 */
array arrInit(array *, int);


/** \fn array arrLoad(array *, int )
 * funzione che carica il vettore con la variabile scelta
 */
array arrLoad(array *, int );


/** \fn int arrSearch(array *, int );

 * funzione che cerca elementi in un array
 */
int arrSearch(array *, int );


/** \fn void arrPrint(array *)
 * funzione che stampa il vettore
 */
void arrPrint(array *);


/** \fn array arrFillavb(array  *, int , int );

 * funzione che inserisce un elemento
 *  nella prima posizione disponibile diversa da x
 */
array arrFillavb(array  *, int , int );


/** \fn int arrCountNotX(array  *, int )
 * funzione che conta tutti gli elementi diversi da x
 */
int arrCountNotX(array  *, int );


/** \fn int arrCountX(array *, int )
 * funzione che  Conta tutti gli elementi uguali x
 */
int arrCountX(array *, int );


/** \fn int arrMaxN(array *arr)
 * funzione che trova l'elemento massimo del vettore
 */
int arrMaxN(array *arr);

#endif /* ARRAYS_H_ */
