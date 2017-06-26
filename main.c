/*! \mainpage La Volpe e La Tartaruga
 * \section intro_sec Introduzione a la volpe e la tartaruga
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "src/game.h"
#include "src/gui.h"
#include "src/tools.h"

int main()
{
	// utilizza l'ora + il clock della cpu come seed per la funzione rand()
	srand( time(NULL) );

	// menu -> input dell'utente - err -> variabile per la gestione degli errori
	int menu, err;
	players players;
	array played;
	array winners;
	array run;
	deck deck;
	int saved_turn;

	/* Settaggi iniziali  */
	saved_turn = 0;
	arrInit(&winners, MAX_PLAYERS);
	arrLoad(&winners, 0);
	arrInit(&run, MAX_CARDS);
	arrInit(&deck.totals, MAX_CARDS);
	arrInit(&played, MAX_PLAYED_CARDS);
	setPositions();
	menu = 0;
	err = 0;
	err = initConsole();

	/* Setta le impostazioni a parametri di default */
	players.n_players = 4;
	createPlayers(&players);
	players.player[0].ai = false;
	players.player[1].ai = true;
	players.player[2].ai = true;
	players.player[3].ai = true;
	players.player[4].ai = false;
	namePlayers(&players);

	while ( err == 0 ){

		printTitle();
		printMenu();

		menu = getch();
		if (menu == '1'){
			// Nuova Partita
			system("cls");
			err = newGame(&players, &played, &deck, &run);
			err = play(&players, &played, &deck, &winners, &run, false, &saved_turn);
			if (err == SAVE_UNABLE){
				errorHandle(err);
				err = 0;
			}
			listErase(deck.card_list);
			namePlayers(&players);
			arrLoad(&winners, 0);
			arrLoad(&run, 0);

		}
		if (menu == '2'){
			// Carica Parita
			system("cls");
			err = loadGame(&winners, &played, &players, &deck, &run, &saved_turn);

			if ( err == 0){
				err = play(&players, &played, &deck, &winners, &run, true, &saved_turn);
				// resetta le impostazioni a default
				namePlayers(&players);
				players.n_players = 4;
				players.player[0].ai = false;
				players.player[1].ai = true;
				players.player[2].ai = true;
				players.player[3].ai = true;
				players.player[4].ai = false;
				listErase(deck.card_list);
				arrLoad(&winners, 0);
				arrLoad(&run, 0);

			} else if ( err == FAILURE){
				err = 0;
			} else if ( err == LOAD_UNABLE){
				errorHandle(err);
				err = 0;
			} else if (err == SAVE_UNABLE){
				errorHandle(err);
				err = 0;
			}
		}
		if (menu == '3'){
			// Impostazioni
			system("cls");
			err = settings(&players);
		}
		if (menu == '4'){
			// Regoole e aiuto
			system("cls");
			err = rules();
		}

		if (menu == 27 ){
			// Esci dal Gioco
			return 0;

		} else {

			system("cls");
		}

	}
	errorHandle(err);

	return 0;
}



