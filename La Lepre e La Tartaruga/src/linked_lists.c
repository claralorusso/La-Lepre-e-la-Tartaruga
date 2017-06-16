#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_lists.h"

/** \fn list init()
 *  Funzione di inizializzazione lista
 *  \return NULL
 *//** \fn list init()
 *  Funzione di inizializzazione lista
 *  \return NULL
 */
list listInit() {
	return NULL;
}

/** \fn boolean listempty(list l)
 *  Controlla che la lista passata sia vuota
 *  \param l lista da controllare
 *  \return 1 se vuota 0 se piena
 */
bool listEmpty(list l) {
	return l == NULL;
}

/** \fn list listpush(list l, int el)
 *  Inserisce un elemento in testa alla lista
 *  \param l lista da modificare
 *  \param el elemento da inserire
 *  \return lista modificata
 */
list listPush(list l, int el) {
	node * temp;
	temp = malloc(sizeof(node));
	temp->data = el;
	temp->next = l;
	return temp;
}

/** \fn list listadd(list l, int el)
 *  Aggiunge un elemento alla fine della lista
 *  \param l lista da modificare
 *  \param el elemento da inserire
 *  \return lista modificata
 */
list listAdd(list l, int el) {
	node * temp;
	if (listEmpty(l) == true) {

		temp = malloc(sizeof(node));
		temp->data = el;
		temp->next = NULL;

	} else {

		l->next = listAdd(l->next, el);
		temp = l;
	}
	return temp;
}

list listDel(list l, int el) {
	node * temp, *current, *previous;

	if (listEmpty(l))
		return l;

	if (l->data == el) {
		temp = l;
		l = l->next;
		free(temp);
	} else {
		previous = NULL;
		current = l;
		while (current != NULL && current->data != el) {
			previous = current;
			current = current->next;
		}
		if (current != NULL && current->data == el) {
			temp = current;
			previous->next = current->next;
			free(temp);
		}
	}
	return l;
}

int listGetLast(list l) {
	node * temp;
	int last;

	if (listEmpty(l))
		return -1;

	if (l->next == NULL) {
		last = l->data;
	} else {
		temp = l;
		while (temp->next != NULL) {

			temp = temp->next;

		}
		if (temp->next == NULL) {
			last = temp->data;
		}
	}
	return last;
}

list listDLast(list l) {
	node * temp, *current, *previous;

	if (listEmpty(l))
		return l;

	if (l->next == NULL) {
		temp = l;
		l = NULL;
		free(temp);
	} else {
		previous = NULL;
		current = l;
		while (current->next != NULL) {
			previous = current;
			previous->next = current->next;
			current = current->next;

		}
		if (current->next == NULL) {
			previous->next = NULL;
			free(current);
		}
	}

	return l;
}
/** \fn list listadd(list l, int el)
 *  Stampa una lista
 *  \param l lista da stampare
 *  \return 0 se la funzione ha avuto buon fine, 1 in ogni altro caso
 */
int listPrint(list l) {
	int error;
	error = 1;
	while (l != NULL) {

		if (printf("%d ", l->data) != 0) {
			error = 0;
		}
		l = l->next;
	}
	return error;
}

int listLenght(list l) {
	int lenght;
	lenght = 0;
	while (l != NULL) {
		lenght++;
		l = l->next;
	}
	return lenght;
}

int listGetRand(list l) {
	int el;
	int count;
	int n;
	node * temp;

	if (listEmpty(l)) {
		return -1;
	}

	n = 0;
	srand(time(NULL));

	count = rand() % listLenght(l);
	temp = l;
	while (temp->next != NULL) {
		n++;
		if (n == count) {
			el = temp->data;
		}
		temp = temp->next;
	}

	return el;
}

void listDelete(list l) {

	node * current = l;
	node * next;

	// Cancella tutti gli elementi della lista
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	l = NULL;
}
