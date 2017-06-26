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
#include "arrays.h"

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


/** \fn list listInit(void)

 * funzione che inizializza una lista
 */
list listInit(void);


/** \fn bool listEmpty(list )

 * funzione che controlla se la lista è vuota
 */
bool listEmpty(list );


/** \fn list listPush(list , int )

 * funzione che aggiunge elemento alla lista dalla testa
 */
list listPush(list , int );


/** \fn list listAdd(list , int )

 * funzione che aggiunge elemento alla lista

 */
list listAdd(list , int );



/** \fn list listAdd(list , int )
 * funzione che cancella elemento dalla lista
 */
list listDel(list , int );

/** \fn int listPrint(list )
 * funzione che stampa lista
 */
int listPrint(list );


/** \fn int listLenght(list )
 * funzione che restituisce lunghezza lista
 */
int listLenght(list );


/** \fn int listGetLast(list )
 * funzione che prende ultimo elemento della lista
 */
int listGetLast(list );


/** \fn list listDLast(list )
 * funzione che cancella ultimo elemento della lista
 */
list listDLast(list );




/** \fn void listErase(list )
 * funzione che rimuove la lista dalla memoria
 */
void listErase(list );


/** \fn array listIntoArray(list l)
 * funzione che aggiunge lista in un array
 */
array listIntoArray(list l);


/** \fn list arrIntoList(array *arr
 * funzione aggiunge array nella lista
 */
list arrIntoList(array *arr);

#endif /* LINKED_LISTS_H_ */



