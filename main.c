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

	/* Settaggi iniziali  */
	arrInit(&winners, 5);
	arrLoad(&winners, 0);
	arrInit(&run, 12);
	arrInit(&deck.totals, 6);
	arrInit(&played, MAX_PLAYED_CARDS);
	setPositions();
	menu = 0;
	err = 0;
	err = initConsole();

	/* Setta le impostazioni a parametri di default */
	players.n_players = 2;
	create_players(&players);
	players.player[0].ai = false;
	players.player[1].ai = true;
	players.player[2].ai = false;
	players.player[3].ai = false;
	players.player[4].ai = false;
	name_players(&players);

	while ( err == 0){

		printTitle();
		printMenu();

		menu = getch();
		if (menu == '1'){

			system("cls");

			err = newGame(&players, &played, &deck, &run);
			err = play(&players, &played, &deck, &winners, &run);

			listErase(deck.card_list);
			name_players(&players);
			arrLoad(&winners, 0);

		}
		if (menu == '2'){

			system("cls");
			err = loadGame();
		}
		if (menu == '3'){

			system("cls");
			err = settings(&players);
		}
		if (menu == '4'){

			system("cls");
			err = rules();
		}
		// esci
		if (menu == 27 ){
			return 0;

		} else {
			system("cls");
		}

	}
	errorHandle(err);

	/* Elimina tutti gli array in memoria*/
	listErase(deck.card_list);
	for (int i = 0; i < players.n_players;i++){
		free(players.player[i].bet_cards.d);
		free(players.player[i].run_cards.d);
		free(players.player[i].name);
	}
	free(players.player);
	free(played.d);

	return 0;
}



