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

int newGame(players *players, array *played, deck *deck, int *turn)
{
	int i, j;

	*turn = 0;

	arrInit(played, MAX_PLAYED_CARDS, false);
	arrLoad(played, 0);

	deck->card_list = listInit();
	deck->totals = arrInit(&deck->totals, 6, false);

	shuffle_deck(deck);

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
	printRoute();

	printStatics();

	printRef();

	//system("pause > nul");

	return 0;
}

int loadGame(void)
{

	system("pause > nul");

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

deck shuffle_deck( deck *deck )
{
	int number;
	srand(time(NULL));
	deck->totals = arrInit(&deck->totals, 6, false);
	deck->totals = arrLoad(&deck->totals, 0);

	while ( deck->totals.d[0] < 81 ){
		number = rand()% 5 + 1;
		if (number == WOLF && deck->totals.d[1] < 16){
			deck->card_list = listAdd(deck->card_list, WOLF);
			deck->totals.d[WOLF]++;
			deck->totals.d[0]++;
		}
		if (number == HARE && deck->totals.d[2] < 18){
			deck->card_list = listAdd(deck->card_list, HARE);
			deck->totals.d[HARE]++;
			deck->totals.d[0]++;
		}
		if (number == TORTOISE && deck->totals.d[3] < 17){
			deck->card_list = listAdd(deck->card_list, TORTOISE);
			deck->totals.d[TORTOISE]++;
			deck->totals.d[0]++;
		}
		if (number == LAMB && deck->totals.d[4] < 15){
			deck->card_list = listAdd(deck->card_list, LAMB);
			deck->totals.d[LAMB]++;
			deck->totals.d[0]++;
		}
		if (number == FOX && deck->totals.d[5] < 15){
			deck->card_list = listAdd(deck->card_list, FOX);
			deck->totals.d[FOX]++;
			deck->totals.d[0]++;
		}

	}
	return *deck;
}

players create_players(players *players, bool allocated)
{
	int i;

	if ( allocated == false){

		players->player = malloc( players->n_players * sizeof(player) );
		i = 0;
		while ( i < players->n_players ){

			// crea giocatori di default
			players->player[i].ai = false;

			players->player[i].bet_cards = arrInit( &players->player[i].bet_cards, MAX_BETS, allocated);
			players->player[i].bet_cards = arrLoad( &players->player[i].bet_cards, 0);

			players->player[i].run_cards= arrInit( &players->player[i].run_cards, MAX_CARDS, allocated);
			players->player[i].run_cards= arrLoad( &players->player[i].run_cards, 0);

			i++;
		}
	}

	if ( allocated == true){
		players->player = realloc(players->player, players->n_players * sizeof(player) );
		i = 0;
		while ( i < players->n_players ){

			// resetta gli array dei giocatori
			players->player[i].bet_cards = arrInit( &players->player[i].bet_cards, MAX_BETS, allocated);
			players->player[i].bet_cards = arrLoad( &players->player[i].bet_cards, 0);

			players->player[i].run_cards= arrInit( &players->player[i].run_cards, MAX_CARDS, allocated);
			players->player[i].run_cards= arrLoad( &players->player[i].run_cards, 0);

			i++;
		}
	}


	return *players;
}

players name_players(players *players_d)
{
	int i;


	i = 0;
	while ( i < players_d->n_players ){

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

int GetCard(deck *deck_d)
{
	int card;
	node * temp;

	card = 0;
	temp = deck_d->card_list;

	//card = listgetlast(temp);
	//deck_d->card_list = listdlast(temp);

	card = listGetRand(temp);
	deck_d->card_list = listDel( temp, card);

	deck_d->totals.d[card]--;
	deck_d->totals.d[0]--;

	return card;
}

players firstBetCard(players *players_d)
{
	int i, n;
	array betcards;

	betcards = arrInit(&betcards,5, false);
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


	return *players_d;
}

int secondBetCard(player player, deck *deck, array *played)
{
	int i, j, pos, input_value, previous;
	char input;
	array temp;
	bool flag;

	pos = - 1;
	arrInit(&temp, 7, false);
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
				return 2;
			}
			if ( input == 27 ){ // in caso venga premuto il tasto esci
				//Torna al menu
				return 1;
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

	if ( (arrCountX(played, played_card) + count) < MAX_TURN && flag == false  && played_card == player->run_cards.d[input-1] && (arrCountNotX(played, 0)+ count) != 8 )
	{
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
		//GotoXY(40,11);
		//printf("Non puoi giocare questa carta!");
		playerErrors();
	}

	flag = false;


	return *pos;
}

//Carta selezionata, su cui si deve basare la selezione delle successive carte
int check_played_card(array *arr)
{
	int px;
	int i = 0;

	while(i < 4)
	{
		if(arr->d[i] != -1)
		{
			px = arr->d[i];
			i = 4;
		}
		i++;
	}
	return px;

}

int play(players *players, array *played, deck *deck, int turn )
{
	//char input;
	//int converted;
	positions positions;
	positions = malloc( 11 * sizeof(coord) );
	array pos;
	pos = arrInit(&pos, 4, false);
	pos = arrLoad(&pos, -1);
	int i, check;

	// Scelta delle seconde carte scommessa
	i = 0;
	while( i < players->n_players ){

		check = secondBetCard(players->player[i], deck, played);

		if ( check == 1){
			// esci
			free(pos.d);
			return 0;

		} else if ( check == 2){
			//salva
			free(pos.d);
			return 0;
		}
		i++;
	}

	GotoXY(44, 19);
	printf("     ");
	GotoXY(44, 20);
	printf("     ");
	GotoXY(44, 21);
	printf("     ");

	// resta nel ciclo finchè non si attiva la fase di corsa
	if( arrCountNotX( played, 0 )  < 8
		|| arrCountX(played, WOLF)
		|| arrCountX(played, HARE)
		|| arrCountX(played, TORTOISE)
		|| arrCountX(played, LAMB)
		|| arrCountX(played, FOX) ){
		turn = 0;
		// i giocatori giocano i loro turni
		while ( turn < players->n_players ){
			// stampa le carte
			printPlayed(played);
			printTurn(players->player[turn].name);
			printBet(&players->player[turn].bet_cards);
			printHand(&players->player[turn].run_cards);

			// caso in cui il giocatore sia umano
			while ( players->player[turn].ai == false){
				turn = playerTurn(players, played, deck, &pos, turn);
			}
			// caso in cui il giocatore sia ia
			if (players->player[turn].ai == true){
				// turno dell'ia
				Sleep(1000);
				iamain( &players->player[turn].run_cards, played, players->player[turn].bet_cards.d[0], players->player[turn].bet_cards.d[1] );

				// stampa le carte
				printPlayed(played);
				printTurn(players->player[turn].name);
				printBet(&players->player[turn].bet_cards);

				i = 0;
				while( i < MAX_CARDS ){
					if( players->player[turn].run_cards.d[i] == 0){
						players->player[turn].run_cards.d[i] = GetCard(deck);
						printHand(&players->player[turn].run_cards);
					}
					i++;
				}
				printPlayed(played);
				printTurn(players->player[turn].name);
				printBet(&players->player[turn].bet_cards);
				printHand(&players->player[turn].run_cards);
				Sleep(1000);
				turn++;
			}

		} // ciclo secondario

	} // ciclo principale

	free(pos.d);
	return 0;
}

int playerTurn(players *players, array *played,deck *deck, array * pos, int turn)
{
	char input;
	int converted;
	int i;

	input = getch();
	converted = input -'0';

	if ( input == 's' || input == 'S' ){
		//salva
		free(pos->d);
		return 0;
	}
	if ( input == 27 ){
		//Torna al menu
		free(pos->d);
		return 0;
	}
	if ( (converted >= 1 && converted <= 6) || input == ' '){

		if ( input == ' ' && arrCountNotX(pos, -1) > 0){
			// fine turno
			i = 0;
			while ( i < MAX_TURN){
				if ( pos->d[i] != -1){
					pos->d[i]--;
				}
				i++;
			}

			i = 0;
			while ( i < MAX_TURN){
				if ( pos->d[i] != -1){
					arrFillavb(played, players->player[turn].run_cards.d[ pos->d[i] ] , 0);
					players->player[turn].run_cards.d[ pos->d[i] ] = 0;
				}
				i++;
			}
			i = 0;
			while( i < MAX_CARDS ){
				if( players->player[turn].run_cards.d[i] == 0){
					players->player[turn].run_cards.d[i] = GetCard(deck);
				}
				i++;
			}
			// resetta le posizioni
			arrLoad(pos, -1);

			// stampa le carte
			printPlayed(played);
			printTurn(players->player[turn].name);
			printBet(&players->player[turn].bet_cards);
			printHand(&players->player[turn].run_cards);

			turn++;
			// rimuove gli indicatori
			GotoXY(0,22);
			printf("                                                                             ");


		} else if (input != ' ' ) {
			playerGetCard( &players->player[turn], played, converted, pos);

			printPlayed(played);
			printTurn(players->player[turn].name);
			printBet(&players->player[turn].bet_cards);
			printHand(&players->player[turn].run_cards);
		}
	}

	return turn;

}

int runPhase(players *players, array *played, positions *positions)
{

	return 0;
}

int setPositions()
{


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
