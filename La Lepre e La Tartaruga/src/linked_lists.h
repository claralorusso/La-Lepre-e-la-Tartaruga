/** \file linked_lists.h
 * \brief header contenente funzione e struttura dati per le linked lists
 * \author Gianluca Caputo
 * \version 0.1
 * \date 2017-05
 *
 *
 */
#ifndef LINKED_LISTS_H_
#define LINKED_LISTS_H_

#include "tools.h"

/** \struct node
 *  Struttura di una lista di interi
 */
typedef struct node{
	/// Il dato contenente nel nodo
	int data;
	/// Indirizzo del nodo succesivo
	struct node *next;
}node;

/** \typedef node * list;
 *  Crea un tipo di dato lista
 */
typedef node *list;


list listInit(void);
bool listEmpty(list );
list listPush(list , int );
list listAdd(list , int );
list listDel(list , int );
int listPrint(list );
int listLenght(list );
int listGetLast(list );
list listDelLast(list );
int listGetRand(list );
void listDelete(list );

#endif /* LINKED_LISTS_H_ */



