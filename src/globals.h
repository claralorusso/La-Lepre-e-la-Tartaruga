#ifndef GLOBALS_H_
#define GLOBALS_H_

/** \def WOLF 1
 *  animale lupo
 */
#define WOLF 1

/** \def HARE 2
 *  animale lepre
 */
#define HARE 2

/** \def TORTOISE 3
 *  animale tartaruga
 */
#define TORTOISE 3

/** \def LAMB 4
 *  animale agnello
 */
#define LAMB 4

/** \def FOX 5
 *  animale volpe
 */
#define FOX 5


#define MAX_CARDS 6
#define MAX_PLAYED_CARDS 8
#define MAX_TURN 4
#define MAX_BETS 2
#define MAX_PLAYERS 5

/// codici di errore

/** \def SAVE_UNABLE 25
 *  non è possibile salvare
 */
#define SAVE_UNABLE 25

/** \def  LOAD_UNABLE 35
 *  non è possibile caricare
 */
#define LOAD_UNABLE 35

/** \def  FAILURE -1
 *  operazione fallita
 */
#define FAILURE -1

/** \def  SAVE_GAME 10
 *  input scelta del salvataggio
 */
#define SAVE_GAME 10

/** \def  BACK_TO_MENU
 *  ritorno al menu
 */
#define BACK_TO_MENU 20

/** \def  RULES_NOT_FOUND 30
 *  errore regole non trovate
 */
#define RULES_NOT_FOUND 30
#endif /* GLOBALS_H_ */
