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
	players players;
	array played;
	deck deck;
	bool allocated;

	/* Settaggi iniziali  */
	allocated = false;
	menu = 0;
	err = 0;
	err = initConsole();

	/* Setta le impostazioni a parametri di default */
	players.n_players = 2;
	players = create_players(&players, allocated);
	players.player[1].ai = true;
	players = name_players(&players);



	while ( err == 0){

		printTitle();
		printMenu();

		menu = getch();
		if (menu == '1'){

			system("cls");

			err = newGame(&players, &played, &deck, &turn);
			err = play(&players, &played, &deck, turn);

			listDelete(deck.card_list);
			players = create_players(&players, allocated);
			players.player[1].ai = true;
			players = name_players(&players);
			free(played.d);
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



