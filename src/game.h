#ifndef GAME_H_
#define GAME_H_
#include "arrays.h"
#include "tools.h"
#include "linked_lists.h"
#include "globals.h"

/** \typedef
 * caratteristiche di un giocatore
 */
typedef struct player{
	char name[15];
	bool ai;
	array bet_cards;
	array run_cards;
	int score;
}player;

/** \typedef
 * Vettore di giocatori
 */
typedef struct players{
	player *player;
	int n_players;
}players;

/** \typedef
 * Lista che definisce il mazzo di carte
 */
typedef struct deck{
	list card_list;
	array totals;
}deck;

/// Funzioni principali del menù
/** \fn int newGame(players *, array *, deck *, array *)
 * Funzione di nuova partita
 */
int newGame(players *, array *, deck *, array *);

/** \fn loadGame(array *winners, array *played, players *p, deck * deck, array *run, int *saved_turn)
 * Funzione di carica partita
 * \param winners posizione vincitori
 * \param played posizione giocatori
 * \param deck stato del mazzo
 * \param run posizioni nel percorso
 * \param saved_turn turno salvato
 */
int loadGame(array *winners, array *played, players *p, deck * deck, array *run, int *saved_turn);

/** \fn int settings(players *)
 * Funzione delle impostazioni
 */
int settings(players *);

/** \fn int rules(void)
 * Funzione delle regole
 */
int rules(void);

/** \fn aveGame(array *winners, array *played, players *p, deck * deck, array *run, int *saved_turn)
 * Funzione salvataggio gioco
 * \param winners posizione vincitori
 * \param played posizione giocatori
 * \param deck stato del mazzo
 * \param run posizioni nel percorso
 * \param saved_turn turno salvato
 */
int saveGame(array *winners, array *played, players *p, deck * deck, array *run, int *saved_turn);


/// Funzioni essenziali del gioco

/** \fn shuffleDeck(deck *)
 * Funzione che mischia il mazzo in maniera casuale
 */
deck shuffleDeck(deck *);

/** \fn shuffleDeck(deck *)
 * Funzione che crea il giocatore
 */
players createPlayers(players *);

/** \fn players namePlayers(players *)
 * Funzione che genera nomi di defult
 */
players namePlayers(players *);

/** \fn int GetCard(deck *)
 * Funzione che prende una carta dal mazzo o chiama la funzione per mescolare
 */
int GetCard(deck *);

/** \fn players firstBetCard(players *)
 * Funzione di scelta della prima carta scommessa
 */
players firstBetCard(players *);

/** \fn int secondBetCard(player , deck *, array *)
 * Funzione di scelta della seconda carta scommessa
 */
int secondBetCard(player , deck *, array *);

/** \fn array playerGetCard(player *, array *, int , array *)
 * Funzione che non fa giocare carte diverse al giocatore
 *  */
array playerGetCard(player *, array *, int , array *);

/** \fn int checkPlayedCards(array *)
 * Funzione che basa la scelta delle altre carte in relazione alla prima scelta
 *  */
int checkPlayedCards(array *);

/** \fn play(players *p, array *, deck *, array *, array * , bool loaded, int *saved_turn)
 * Funzione del gioco
 * \param loaded booleano che verifica il caricamento
 */
int play(players *p, array *, deck *, array *, array * , bool loaded, int *saved_turn);

/** \fn int playerTurn(players *, array *,deck *, array *, int )
 * Funzione gestione del turno
 *
 */
int playerTurn(players *, array *,deck *, array *, int );

/** \fn bool runPhase(players *, array *, array *, array *)
 * Funzione che verifica l'attivazione della fase di corsa
 *
 */
bool runPhase(players *, array *, array *, array *);

/** \fn void StandPositions(array *run, array *)
 * Funzione che verifica se sono arrivati alla fine del percorso gli animali
 *
 */
void StandPositions(array *run, array *);

/** \fn int getMaxScore(players *p)
 * Funzione restituisce il punteggio massimo
 *
 */
int getMaxScore(players *p);

/** \fn void sortScore( players *p )
 * Funzione che ordina i punteggi in ordine decrescente
 *
 */
void sortScore( players *p );

/** \fn void scores(players *players, array *winners)
 * Funzione che assegna punteggi ai giocatori
 *
 */
void scores(players *players, array *winners);

/// Funzioni di gestione
/** \fn void errorHandle(int error)
 * Funzione di errore
 */
void errorHandle(int error);

/** \fn int initConsole(void)
 * Funzione inizializza la console per il gioco
 */
int initConsole(void);

#endif /* GAME_H_ */

