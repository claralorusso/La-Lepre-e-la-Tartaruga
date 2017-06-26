/*
 * error_msg.h
 *
 *  Created on: 30 mag 2017
 *      Author: Gianluca
 */

#ifndef ERROR_MSG_H_
#define ERROR_MSG_H_

/** \fn void printErrorGeneric(void)
 * Messaggio di errore generico
 */
void printErrorGeneric(void);


/** \fn void printErrorLoadUnable(void)
 * Messaggio di errore caricamento
 */
void printErrorLoadUnable(void);


/** \fn void printErrorSaveUnable(void)
 * Messaggio di errore salvataggio
 */
void printErrorSaveUnable(void);


/** \fn void printErrorNoRules(void)
 * Messaggio di errore regole
 */

void printErrorNoRules(void);

#endif /* ERROR_MSG_H_ */
