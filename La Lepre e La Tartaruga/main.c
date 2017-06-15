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
	int menu, err; // menu -> input dell'utente - err -> variabile per la gestione degli errori
	int turn;
	int i;
	players players;
	array played;
	deck deck;

	/* Setta le impostazioni a parametri di default */
	players.n_players = 2;
	players.player[1].ai = true;
	players = create_players(&players);
	players = name_players(&players);

	err = 0;
	err = initConsole();

	while ( err == 0){

		printTitle();
		printMenu();

		menu = getch();
		if (menu == '1'){

			system("cls");
			err = newGame(&players, &played, &deck, &turn);
			err = play(&players, &played, &deck, turn);
			listDelete(deck.card_list);
			i = 0;
			while ( i < players.n_players){
				free(&players.player[i].bet_cards.d);
				free(&players.player[i].run_cards.d);

				players.player[i].bet_cards.d = NULL;
				players.player[i].run_cards.d = NULL;

				i++;
			}
			free(players.player);
			free(played.d);
			players.player = NULL;
			played.d = NULL;

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
		if (menu == 27 ){
			return 0;

		} else {
			system("cls");
		}

	}
	errorHandle(err);

	return 0;
}



