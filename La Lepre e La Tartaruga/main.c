/*! \mainpage La Volpe e La Tartaruga
 * \section intro_sec Introduzione a la volpe e la tartaruga
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "src/game.h"
#include "src/gui.h"
#include "src/tools.h"

int main()
{
	// menu -> input dell'utente - err -> variabile per la gestione degli errori
	int menu, err;
	players players;
	array played;
	deck deck;

	/* Settaggi iniziali  */
	arrInit(&deck.totals, 6);
	arrInit(&played, MAX_PLAYED_CARDS);
	menu = 0;
	err = 0;
	err = initConsole();

	/* Setta le impostazioni a parametri di default */
	players.n_players = 5;
	create_players(&players);
	//players.player[1].ai = true;
	name_players(&players);

	while ( err == 0){

		printTitle();
		printMenu();

		menu = getch();
		if (menu == '1'){

			system("cls");

			err = newGame(&players, &played, &deck);
			err = play(&players, &played, &deck);

			listDelete(deck.card_list);
			name_players(&players);

		}
		if (menu == '2'){

			system("cls");
			err = loadGame();
		}
		if (menu == '3'){

			system("cls");
			err = settings();
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
	listDelete(deck.card_list);
	for (int i = 0; i < players.n_players;i++){
		free(players.player[i].bet_cards.d);
		free(players.player[i].run_cards.d);
		free(players.player[i].name);
	}
	free(players.player);
	free(played.d);

	return 0;
}



