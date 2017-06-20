#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "game.h"
#include "linked_lists.h"
#include "arrays.h"
#include "gui.h"
#include "error_msg.h"
#include "ia.h"
#include "tools.h"

#define SAVE_GAME 10
#define BACK_TO_MENU 20


int newGame(players *players, array *played, deck *deck)
{
	int i, j;

	/* Resetta le Carte Giocate */
	arrLoad(played, 0);

	/* Prepara il mazzo*/
	deck->card_list = listInit();
	shuffle_deck(deck);

	/* Resetta le Carte Scommessa*/
	i = 0;
	while( i < players->n_players ){
		arrLoad(&players->player[i].bet_cards, 0);
		i++;
	}

	/* Assegna ai giocatori le prime Carte Scommessa e le Carte Corsa */
	firstBetCard(players);
	j = 0;
	while( j < players->n_players ){
		i = 0;
		while(i < MAX_CARDS){

			players->player[j].run_cards.d[i] = GetCard(deck);
			i++;
		}
		j++;
	}

	/* Stamp l'intefaccia di base*/
	printRoute();
	printAnimal(0, 0);
	printStatics();
	printRef();

	return 0;
}

int loadGame(void)
{
	deck deck;
	int test;
	int i;
	arrInit(&deck.totals, 6);
	deck.card_list = listInit();
	shuffle_deck(&deck);
	printf("\n");
	i = 0;
	while(1){

		test = GetCard(&deck);
		printf("%d", test);
		i++;
		if ( i == 5){
			printf("\n");
			i = 0;
		}
	}


	return 0;
}

int settings(void)
{

	system("pause > nul");
	return 0;
}

int rules(void)
{
	system("pause > nul");
	return 0;

}

void saveGame()
{
	system("cls");
	printf("Funzione ancora da implementare!\n");
	system("pause > nul");
}

deck shuffle_deck( deck *deck )
{
	int number;

	deck->totals = arrLoad(&deck->totals, 0);

	while ( deck->totals.d[0] < 81){

		number = rand()% 5 + 1;

		if (number == WOLF && deck->totals.d[WOLF] < 16){
			deck->card_list = listAdd(deck->card_list, WOLF);
			deck->totals.d[WOLF]++;
			deck->totals.d[0]++;
		}
		if (number == HARE && deck->totals.d[HARE] < 18){
			deck->card_list = listAdd(deck->card_list, HARE);
			deck->totals.d[HARE]++;
			deck->totals.d[0]++;
		}
		if (number == TORTOISE && deck->totals.d[TORTOISE] < 17){
			deck->card_list = listAdd(deck->card_list, TORTOISE);
			deck->totals.d[TORTOISE]++;
			deck->totals.d[0]++;
		}
		if (number == LAMB && deck->totals.d[LAMB] < 15){
			deck->card_list = listAdd(deck->card_list, LAMB);
			deck->totals.d[LAMB]++;
			deck->totals.d[0]++;
		}
		if (number == FOX && deck->totals.d[FOX] < 15){
			deck->card_list = listAdd(deck->card_list, FOX);
			deck->totals.d[FOX]++;
			deck->totals.d[0]++;
		}
	}

	return *deck;
}

players create_players(players *players)
{
	int i;

	players->player = malloc( MAX_PLAYERS * sizeof(player) );
	i = 0;
	while ( i < MAX_PLAYERS ){

		// crea giocatori di default
		players->player[i].ai = false;

		players->player[i].bet_cards = arrInit( &players->player[i].bet_cards, MAX_BETS);
		players->player[i].bet_cards = arrLoad( &players->player[i].bet_cards, 0);

		players->player[i].run_cards= arrInit( &players->player[i].run_cards, MAX_CARDS);
		players->player[i].run_cards= arrLoad( &players->player[i].run_cards, 0);

		i++;
	}

	return *players;
}

players name_players(players *players_d)
{
	int i;

	i = 0;
	while ( i < MAX_PLAYERS ){

		if (players_d->player[i].ai == false){
			strcpy(players_d->player[i].name, "Giocatore");
			players_d->player[i].name[9] = 49 + i;
			players_d->player[i].name[10] = '\0';

		} else if (players_d->player[i].ai == true){
			strcpy(players_d->player[i].name, "I.A.       ");
		}

		i++;
	}

	return *players_d;
}

int GetCard(deck *deck)
{
	int card;

	card = 0;

	// se il mazzo è finito lo rimescola
	if ( listEmpty(deck->card_list) ){
		shuffle_deck(deck);
	}

	// Prende l'ultima carta del mazzo e la elimina
	card = listGetLast(deck->card_list);
	deck->card_list = listDLast( deck->card_list);

	// Riduce i totali delle carte
	deck->totals.d[card]--;
	deck->totals.d[0]--;

	return card;
}

players firstBetCard(players *players_d)
{
	int i, n;
	array betcards;
	srand(time(NULL));
	betcards = arrInit(&betcards,5);
	betcards.d[0] = WOLF;
	betcards.d[1] = HARE;
	betcards.d[2] = TORTOISE;
	betcards.d[3] = LAMB;
	betcards.d[4] = FOX;
	i = 0;

	while ( i < players_d->n_players ){
		n = rand() % 5;
		if ( betcards.d[n] != 0){
			players_d->player[i].bet_cards.d[0] = betcards.d[n];
			betcards.d[n] = 0;
			i++;
		}
	}
	free(betcards.d);

	return *players_d;
}

int secondBetCard(player player, deck *deck, array *played)
{
	int i, j, pos, input_value, previous;
	char input;
	array temp;
	bool flag;
	previous = 0;
	pos = - 1;
	arrInit(&temp, 7);
	arrLoad(&temp, 0);

	// carica il vettore temporaneo per la settima carta scommessa
	i = 0;
	while ( i < MAX_CARDS){
		temp.d[i] = player.run_cards.d[i];
		i++;
	}
	temp.d[6] = GetCard(deck);
	flag = true;
	while( flag == true){

			printPlayed(played);
			printTurn(player.name);
			printBet(&player.bet_cards);
			printHand(&temp);
		/*
		if (player.ai == true){
			// ia2betcard
		} else */if ( player.ai == false || player.ai == true ) {

			input = getch();
			input_value = input -'0';

			if ( input == 's' || input == 'S' ){ // in caso venga premuto il tasto per salvare
				//salva
				return SAVE_GAME;
			}
			if ( input == 27 ){ // in caso venga premuto il tasto esci
				//Torna al menu
				return BACK_TO_MENU;
			}
			if ( (input_value >= 1 && input_value <= 7)){

				pos = input_value - 1;

				if( player.bet_cards.d[1] == 0 ){
					// Seleziona la carta
					player.bet_cards.d[1] = temp.d[pos];
					printPointer(pos, false);

				}else if ( previous == pos ){
					// Rimuove il puntatore e la carta
					printPointer(pos, true);
					player.bet_cards.d[1] = 0;

				}else if ( player.bet_cards.d[1] != 0 ){
					// Sposta l'indicatore
					printPointer(previous, true);
					player.bet_cards.d[1] = temp.d[pos];
					printPointer(pos, false);
				}
			}
			if ( player.bet_cards.d[1] != 0 && input == ' ' ){
				GotoXY(0,22);
				printf("                                                                             ");
				temp.d[pos] = 0;
				flag = false;
			}
			previous = pos;
		}
	}

	// Riporta i valori nel vettore del giocatore
	i = 0;
	j = 0;
	while ( i < 7){
		if ( temp.d[i] != 0){
			player.run_cards.d[j] = temp.d[i];
			j++;
		}
		i++;
	}
	free(temp.d);
	return 0;
}

array playerGetCard(player *player, array *played, int input, array *pos)
{

	bool flag;
	int i, count;
	int played_card;
	int check = 0;

	/* Conta quante carte mancanti ha il giocatore */
	count = arrCountNotX(pos, -1);
	flag = false;

	//Impedisce di giocare carte di animali diversi
	if(count >= 1)
	{
		check = check_played_card(pos);
		played_card = player->run_cards.d[check-1];
	} else {
		played_card = player->run_cards.d[input-1];
	}

	i = 0;
	while ( i < MAX_TURN){

		if (pos->d[i] == input){
			flag = true;
			printPointer(input-1, flag);
			pos->d[i] = -1;
			count--;
			i = MAX_TURN;

		} else {
			i++;
		}
	}

	if ( (arrCountX(played, played_card) + count) < MAX_TURN && flag == false  && played_card == player->run_cards.d[input-1] && (arrCountNotX(played, 0)+ count) != 8 ){

		count++;
		arrFillavb(pos, input, -1);
		count = arrCountNotX(pos, -1);
		printPointer(input-1, flag);
	} else if ((arrCountX(played, played_card) + count) < MAX_TURN && flag == false  && count == 0 && (arrCountNotX(played, 0)+ count) != 8){

		count++;
		arrFillavb(pos, input, -1);
		count = arrCountNotX(pos, -1);
		printPointer(input-1, flag);

	}else if(flag == false){

		/* Mostra il messaggio di errore al giocatore*/
		playerErrors();
	}
	flag = false;

	return *pos;
}

//Carta selezionata, su cui si deve basare la selezione delle successive carte
int check_played_card(array *arr)
{
	int i, x;
	i = 0;
	x = 0;

	while(i < 4)
	{
		if(arr->d[i] != -1)
		{
			x = arr->d[i];
			i = 4;
		}
		i++;
	}
	return x;

}

int play(players *players, array *played, deck *deck)
{
	int i, check;
	int turn;
	int player_decision;
	array pos, run;
	bool finish;

	run = arrInit(&run, 6);
	run = arrLoad(&run, 0);
	pos = arrInit(&pos, 4);
	pos = arrLoad(&pos, -1);

	finish = false;

	// Scelta delle seconde carte scommessa
	i = 0;
	while( i < players->n_players ){

		check = secondBetCard(players->player[i], deck, played);

		if ( check == SAVE_GAME){
			// salva
			saveGame();
			free(pos.d);
			return 0;

		} else if ( check == BACK_TO_MENU){
			//esci senza salvare

			free(pos.d);
			return 0;
		}
		i++;
	}

	/* Rimuove la settima carta dallo schermo */
	GotoXY(44, 19);
	printf("     ");
	GotoXY(44, 20);
	printf("     ");
	GotoXY(44, 21);
	printf("     ");

	// resta nel ciclo finchè non finisce la partita
	while(finish == false){

		turn = 0;
		// fase di gioco

		while ( turn < players->n_players ){
			// stampa le carte
			printPlayed(played);
			printTurn(players->player[turn].name);
			printBet(&players->player[turn].bet_cards);
			printHand(&players->player[turn].run_cards);

			// caso in cui il giocatore sia umano
			if ( players->player[turn].ai == false ){

				player_decision = playerTurn(players, played, deck, &pos, turn);

				if ( player_decision == SAVE_GAME){
					free(pos.d);
					saveGame();
					//salva
					return 0;
				}
				if ( player_decision == BACK_TO_MENU){
					free(pos.d);
					// esci senza salvare
					return 0;
				}

				// stampa le carte
				printPlayed(played);
				printTurn(players->player[turn].name);
				printBet(&players->player[turn].bet_cards);
				printHand(&players->player[turn].run_cards);
				//}
			// caso in cui il giocatore sia ia
			} else if (players->player[turn].ai == true){

				// turno dell'ia
				printTurn(players->player[turn].name);
				printBet(&players->player[turn].bet_cards);
				printPlayed(played);
				printHand(&players->player[turn].run_cards);
				iamain( &players->player[turn].run_cards, played, players->player[turn].bet_cards.d[0], players->player[turn].bet_cards.d[1] );

				// stampa le carte
				GotoXY(25, 22);
				printf(">>L'IA STA GIOCANDO<<");
				Sleep(1500);
				printPlayed(played);

				i = 0;
				while( i < MAX_CARDS ){
					if( players->player[turn].run_cards.d[i] == 0){
						players->player[turn].run_cards.d[i] = GetCard(deck);

					}
					i++;
				}

				printPlayed(played);
				printTurn(players->player[turn].name);
				printBet(&players->player[turn].bet_cards);
				printHand(&players->player[turn].run_cards);
				Sleep(1000);
				GotoXY(0,22);
				printf("                                                                             ");
			}
			turn++;

		} // fase di gioco
		turn = 0;

		// Condizioni di attivazione fase di corsa
		if(
		  arrCountNotX(played, 0) == 8
		||arrCountX(played, WOLF) == 4
		||arrCountX(played, HARE) == 4
		||arrCountX(played, TORTOISE) == 4
		||arrCountX(played, LAMB) == 4
		||arrCountX(played, FOX) == 4 ) {

			runPhase(players, played, &run);
		}
		arrLoad(played, 0);
		printPlayed(played);
		printTurn(players->player[turn].name);
		printBet(&players->player[turn].bet_cards);
		printHand(&players->player[turn].run_cards);

	} // fine partita

	//free(pos.d);
	return 0;
}

int playerTurn(players *players, array *played,deck *deck, array * pos, int turn)
{
	char input;
	int converted;
	int i;

	while ( arrCountX(played, 0) >= 1 ){
		input = getch();
		converted = input -'0';

		if ( input == 's' || input == 'S' ){
			//salva
			return SAVE_GAME;
		}
		if ( input == 27 ){
			//Torna al menu
			return BACK_TO_MENU;
		}
		// fine turno
		if ( input == ' ' && arrCountNotX(pos, -1) > 0){
			// gioca le carte selezionate
			i = 0;
			while ( i < MAX_TURN){
				if ( pos->d[i] != -1){
					arrFillavb(played, players->player[turn].run_cards.d[ pos->d[i]-1 ] , 0);
					players->player[turn].run_cards.d[ pos->d[i]-1 ] = 0;
				}
				i++;
			}
			// Prende le carte mancanti dal mazzo
			i = 0;
			while( i < MAX_CARDS ){
				if( players->player[turn].run_cards.d[i] == 0){
					players->player[turn].run_cards.d[i] = GetCard(deck);
				}
				i++;
			}
			// resetta le posizioni
			arrLoad(pos, -1);

			// rimuove gli indicatori
			GotoXY(0,22);
			printf("                                                                             ");
			return 0;
		}
		if ( (converted >= 1 && converted <= 6)){

			playerGetCard( &players->player[turn], played, converted, pos);
		}
	}
	return 0;

}

int runPhase(players *players, array *played, array *run)
{
	array path;
	int move, arrive;

	arrInit( &path, 11);
	arrLoad( &path,0);

	path.d[3] = 1;
	path.d[7] = 1;

	move = 0;
	//spostamento lupo
	if ( arrCountX(played, WOLF) == 1 || arrCountX(played, WOLF) == 2 ){
		move = 1;
		arrive = move + run->d[WOLF];

		while ( run->d[WOLF] != arrive ){
			Sleep(200);
			run->d[WOLF] ++;
			printAnimal(WOLF, run->d[WOLF] );
		}

	} else if ( arrCountX(played, WOLF) == 3 || arrCountX(played, WOLF) == 4 ){
		move = arrCountX(played, WOLF) - 1;
		arrive = move + run->d[WOLF];

		while ( run->d[WOLF] != arrive ){
			Sleep(200);
			run->d[WOLF] ++;
			printAnimal(WOLF, run->d[WOLF] );

		}
	}

	//spostamento lepre
	if ( arrCountX(played, HARE) > 0  && arrCountX(played, HARE) <= 4) {
		move = 2;
		arrive = move + run->d[HARE];
		while ( run->d[HARE] != arrive ){
			Sleep(200);
			run->d[HARE]++;
			printAnimal(HARE, run->d[HARE]);
		}
	}

	//spostamento tartaruga
	if ( arrCountX(played, TORTOISE) >= 0  &&  arrCountX(played, TORTOISE) <= 3 ) {
		move = 1;
		arrive = move + run->d[TORTOISE];
		while ( run->d[TORTOISE] != arrive ){
			Sleep(200);
			run->d[TORTOISE] ++;
			printAnimal(TORTOISE, run->d[TORTOISE] );
		}
	} else if (arrCountX(played, TORTOISE) == 4){
		move = 2;
		arrive = move + run->d[TORTOISE];
		while ( run->d[TORTOISE] != arrive ){
			Sleep(200);
			run->d[TORTOISE] ++;
			printAnimal(TORTOISE, run->d[TORTOISE] );
		}
	}

	//spostamento agnello
	if ( arrCountX(played, LAMB) > 0 ) {
		move = arrCountX(played, LAMB) + 1;
		arrive = move + run->d[LAMB];
		while ( run->d[LAMB] != arrive ){
			Sleep(200);
			run->d[LAMB] ++;
			printAnimal(LAMB, run->d[LAMB] );
		}
	}

	//spostamento volpe
	if ( arrCountX(played, FOX) > 0 ) {
		move = arrCountX(played, FOX);
		arrive = move + run->d[FOX];
		while ( run->d[FOX] != arrive ){
			Sleep(100);
			run->d[FOX] ++;
			printAnimal(FOX, run->d[FOX] );
		}
	}

	free(path.d);


	return 0;
}


void errorHandle(int error)
{
	if ( error == 1){
		printErrorGeneric();

	} else {
		printErrorGeneric();

	}
	system("pause >nul");
	return ;
}

int initConsole(void)
{
	system("mode 80,25");

	hidecursor();

	consoleTitle("La Lepre e La Tartaruga");

	return 0;
}
