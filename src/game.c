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


int newGame(players *players, array *played, deck *deck, array *run)
{
	int i, j;

	/* Azzera le posizioni dei giocatori*/
	arrLoad(run, 0);
	/* Resetta le Carte Giocate */
	arrLoad(played, 0);

	/* Prepara il mazzo*/
	deck->card_list = listInit();
	shuffleDeck(deck);

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

int saveGame(array *winners, array *played, players *p, deck * deck)
{
	FILE * save;
	array temp;

	if ( (save = fopen("sav\\Salvataggio.sav", "wb") ) == NULL ){
		return 11;
	}

	fwrite(winners, sizeof(array), 1, save );

	fwrite(played, sizeof(array), 1, save );

	fwrite(p, sizeof(players), 1, save );

	fwrite(&(deck->totals), sizeof(array), 1, save );

	temp = listIntoArray(deck->card_list);

	fwrite( &(temp), sizeof(temp), 1, save );

	fclose(save);



	return 0;
}

int loadGame(array *winners, array *played, players *p, deck * deck)
{
	array temp;
	FILE * save;

	if ( (save = fopen("sav\\Salvataggio.sav", "rb") ) == NULL ){
		return 11;
	}

	fread(winners, sizeof(array), 1, save );

	fread(played, sizeof(array), 1, save );

	fread(p, sizeof(players), 1, save );

	fread(&deck->totals, sizeof(array), 1, save );

	fread( &temp, sizeof(temp), 1, save );

	fclose(save);

	deck->card_list = arrIntoList(&temp);

	/*
	printf("Winners\n");
	arrPrint(winners);

	printf("Played\n");
	arrPrint(played);

	int i = 0;
	while (i < p->n_players){
		printf("%-15s tipo %d carta scommessa 1 %d carta scommessa 2 %d\n",
				p->player[i].name, p->player[i].ai,p->player[i].bet_cards.d[0], p->player[i].bet_cards.d[1]   );
		i++;
	}

	printf("totals\n");
	arrPrint(&deck->totals);

	printf("Deck\n");
	arrPrint(&temp);
	system("pause");
	listPrint(deck->card_list);

	system("pause");

	*/

	return 0;
}

int settings(players *p)
{
	char input;
	int i;
	int setting;
	char type[10], name[15];
	players temp;
	coord angle1, angle2, start;

	start.x = 25;
	start.y = 6;

	angle1.x = start.x - 3;
	angle1.y = start.y - 2;

	angle2.x = start.x + 25;
	angle2.y = start.y + 7;

	// Stampa elementi statici
	GotoXY(start.x, start.y);
	printf(RED"Numero Giocatori: "BLACK);
	printStaticsSettings();
	drawSquare( angle1,  angle2);

	// Alloca lo spazio per il vettore temporaneo
	createPlayers(&temp);
	// Copia le variabile necessarie per le successive modifiche
	temp.n_players = p->n_players;
	namePlayers(&temp);
	i = 0;
	while ( i < temp.n_players ){
		temp.player[i].ai = p->player[i].ai;
		strcpy(temp.player[i].name,  p->player[i].name) ;
		i++;
	}

	// Ciclo principale dell'input
	input = 0;
	setting = 0;
	while ( input != ' ' || input != 27 ){

		if ( SelectorMovement( input, start, &setting, temp.n_players ) == 1 ) return 0;

		GotoXY(start.x + 19, start.y);
		printf("%-1d", temp.n_players );

		i = 0;
		while ( i < temp.n_players  ){

			// Controlla il tipo di giocatore
			if ( temp.player[i].ai == false ){
				strcpy(type, "Umano");
			}
			if ( temp.player[i].ai == true ){
				strcpy(type, "I.A.");
			}
			// Stampa i giocatori
			GotoXY(start.x, (start.y + 1) + i);
			printf("%-15s%-4s"RED"%-5s"BLACK, temp.player[i].name, " -> ", type);
			i++;
		}

		input = getch();
		if ( setting == 0 ){

			if ( ( input == 'd' || input == 'D' ) && temp.n_players  < 5 ){
				temp.n_players ++;
			} else if ( (input == 'a' || input == 'A') && temp.n_players  > 2){
				temp.n_players --;

				// cancella da schermo giocatori non esistenti
				if (temp.n_players  == MAX_PLAYERS - 1){

					GotoXY(0, start.y + MAX_PLAYERS);
					printf("                                                                        ");
				} else if (temp.n_players  == MAX_PLAYERS - 2){
					GotoXY(0, start.y + MAX_PLAYERS - 1);
					printf("                                                                        ");
				} else if (temp.n_players  == MAX_PLAYERS - 3){
					GotoXY(0, start.y + MAX_PLAYERS - 2);
					printf("                                                                        ");
				}

			}
		} else if ( setting >= 1 && setting <= 5){

			if ( ( input == 'd' || input == 'D' ) && temp.player[setting - 1].ai != true ){

				temp.player[setting - 1].ai = true;
				GotoXY(start.x + 19, (start.y + 1) + setting - 1);
				printf("        ");
				GotoXY(start.x + 19, (start.y + 1) + setting - 1);
				printf("I.A.");
			} else if ( (input == 'a' || input == 'A') && temp.player[setting - 1].ai != false ){

				temp.player[setting - 1].ai = false;
				GotoXY(start.x + 19, (start.y + 1) + setting - 1);
				printf("      ");
				GotoXY(start.x + 19, (start.y + 1) + setting - 1);
				printf("Umano");

			} else if ( (input == 'c' || input == 'C') ){

				// richiede nuovo nome
				GotoXY(5, start.y + MAX_PLAYERS + 5);
				printf("Inserire nome Giocatore (MAX 15 CARATTERI) -> ");

				// utilizza una variabile di appoggio per ottenere il nome
				gets(name);
				// controlla che il nuovo nome sia valido
				if ( strlen(name) <= 0 || strlen(name) > 15){
					strcpy(name, temp.player[setting - 1].name );
					GotoXY(25, start.y + MAX_PLAYERS + 7);
					printf("NOME NON VALIDO");
					Sleep(500);
					GotoXY(25, start.y + MAX_PLAYERS + 7);
					printf("               ");
				}
				// se il nuovo nome è valido lo inserisce nella varibile del giocatore
				if ( strlen(name) > 0 && strlen(name) <= 15){
					strcpy(temp.player[setting - 1].name, name );
				}
				// Cancella vecchio nome giocatore
				GotoXY(25, (start.y + 1) + setting - 1);
				printf("                    ");
				// Cancella frase
				GotoXY(5, start.y + MAX_PLAYERS + 5);
				printf("                                                                                        ");
			}
		}
		drawSquare( angle1,  angle2);
	}

	return 0;
}

int rules(void)
{	/*
	char list[10000];
	FILE * test;

	ListDirectoryContents("sav\\", list);

	printf("%s", list);

	if ( (test = fopen("test.txt", "w") ) == NULL){
		return 0;
	}
	fprintf(test,"%s",list);
	*/
	int saveN;
	saveN = getFileQuantity("sav\\", ".sav");
	printf("%d" , saveN);




	system("pause > nul");
	return 0;

}

deck shuffleDeck( deck *deck )
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

players createPlayers(players *p)
{
	int i;

	p->player = malloc( MAX_PLAYERS * sizeof(player) );
	i = 0;
	while ( i < MAX_PLAYERS ){

		// crea giocatori di default
		p->player[i].ai = false;

		p->player[i].bet_cards = arrInit( &p->player[i].bet_cards, MAX_BETS);
		p->player[i].bet_cards = arrLoad( &p->player[i].bet_cards, 0);

		p->player[i].run_cards = arrInit( &p->player[i].run_cards, MAX_CARDS);
		p->player[i].run_cards = arrLoad( &p->player[i].run_cards, 0);

		p->player[i].score = 0;

		i++;
	}

	return *p;
}

players namePlayers(players *p)
{
	int i;

	i = 0;
	while ( i < MAX_PLAYERS ){

			strcpy(p->player[i].name, "Giocatore");
			p->player[i].name[9] = 49 + i;
			p->player[i].name[10] = '\0';

		i++;
	}

	return *p;
}

int GetCard(deck *deck)
{
	int card;

	card = 0;

	// se il mazzo è finito lo rimescola
	if ( listEmpty(deck->card_list) ){
		shuffleDeck(deck);
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
			printTurn(player.name, player.ai);
			printBet(&player.bet_cards);
			printHand(&temp);

		if (player.ai == true){
			GotoXY(17, 22);
			printf(">>L'IA STA SCEGLIENDO<<");
			Sleep(1000);
			player.bet_cards.d[1] = ia2betcard(&temp, player.bet_cards.d[0]);
			GotoXY(0,22);
			printf("                                                                             ");
			Sleep(1000);
			flag = false;
		} else if ( player.ai == false) {

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
		check = checkPlayedCards(pos);
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
int checkPlayedCards(array *arr)
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

int play(players *players, array *played, deck *deck, array *winners, array *run)
{
	int i; // Indice
	int turn; // Indica il turno del giocatore
	int player_decision; // Input del giocatore
	array pos; // Posizioni delle carte giocate dal giocatore
	bool finish; // Controlla che il gioco sia finito

	printRoute();
	printAnimal(0, 0);
	printStatics();
	printRef();

	// Alloca e carica pos
	pos = arrInit(&pos, 4);
	pos = arrLoad(&pos, -1);
	//Setta il flag di fine partita
	finish = false;

	// Scelta delle seconde carte scommessa

	i = 0;
	while( i < players->n_players ){
		// controlla che il giocatore non abbia già una carta scommessa
		if ( players->player[i].bet_cards.d[1] == 0 ){

			player_decision = secondBetCard(players->player[i], deck, played);
		}

		if ( player_decision == SAVE_GAME){
			// salva
			saveGame(winners, played, players, deck);
			free(pos.d);
			return 0;

		} else if ( player_decision == BACK_TO_MENU){
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
	/*--------------------------------------- */

	player_decision = 0;
	// resta nel ciclo finchè non finisce la partita
	while(finish == false){

		turn = 0;
		// fase di gioco

		while ( turn < players->n_players ){

			// stampa le carte
			printPlayed(played);
			printTurn(players->player[turn].name, players->player[turn].ai);
			printBet(&players->player[turn].bet_cards);
			printHand(&players->player[turn].run_cards);

			// caso in cui il giocatore sia umano
			if ( players->player[turn].ai == false ){

				player_decision = playerTurn(players, played, deck, &pos, turn);

				if ( player_decision == SAVE_GAME){
					free(pos.d);
					saveGame(winners, played, players, deck);
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
				printTurn(players->player[turn].name, players->player[turn].ai);
				printBet(&players->player[turn].bet_cards);
				printHand(&players->player[turn].run_cards);

			// caso in cui il giocatore sia ia
			} else if (players->player[turn].ai == true){

				// turno dell'ia
				printTurn(players->player[turn].name, players->player[turn].ai);
				printBet(&players->player[turn].bet_cards);
				printPlayed(played);
				printHand(&players->player[turn].run_cards);
				iamain( &players->player[turn].run_cards, played, players->player[turn].bet_cards.d[0], players->player[turn].bet_cards.d[1] );

				// stampa le carte
				GotoXY(17, 22);
				printf(">>L'IA STA GIOCANDO<<");

				// Da il numero di carte necessarie all'ia
				i = 0;
				while( i < MAX_CARDS ){
					if( players->player[turn].run_cards.d[i] == 0){
						players->player[turn].run_cards.d[i] = GetCard(deck);
					}
					i++;
				}
				//Sleep(1000);
				printPlayed(played);
				printHand(&players->player[turn].run_cards);
				//Sleep(1000);
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

			finish = runPhase(players, played, run, winners);
		}
		arrLoad(played, 0);
		printPlayed(played);
		printTurn(players->player[turn].name, players->player[turn].ai);
		printBet(&players->player[turn].bet_cards);
		printHand(&players->player[turn].run_cards);

	} // fine partita

	system("cls");
	scores(players, winners);
	sortScore(players);
	/*
	i = 0;
	while ( i < players->n_players ){
		printf("\ngiocatore:%d score:%d", i + 1 , players->player[i].score);
		i++;
	}
	*/


	//free(pos.d);
	return 0;
}

void scores(players *players, array *winners)
{
	int i;
	int j;

	i = 0;
	while ( i < players->n_players ){
		j = 0;
		while( j < 2 ){
			if ( winners->d[ ( players->player[i].bet_cards.d[j] ) - 1 ] == 1){
				players->player[i].score = players->player[i].score + 5;
			} else if ( winners->d[ ( players->player[i].bet_cards.d[j] ) - 1 ] == 2){
				players->player[i].score = players->player[i].score + 3;
			}else if ( winners->d[ ( players->player[i].bet_cards.d[j] ) - 1 ] == 3){
				players->player[i].score = players->player[i].score + 2;
			}
			j++;
		}
		i++;
	}
}
int getMaxScore(players *p)
{
	int i;
	int max;

	max = p->player[0].score;

	i = 0;
	while ( i < p->n_players ){
		if ( max < p->player[i].score){

			max = p->player[i].score;
		}
		i++;
	}

	return max;
}

void sortScore( players *p )
{
	int i, j;
	int max;
	array order;
	arrInit(&order,5);
	arrLoad(&order,0);

	max = getMaxScore(p);
	j = 0;
	while ( max >= 0){
		i = 0;
		while (i < p->n_players ){
			if ( max == p->player[i].score ){
				order.d[j] = i;
				j++;
			}
			i++;
		}
		max--;
	}
	printScore(p, &order);

	i = 0;
	while ( i < p->n_players ){
		p->player[i].score = 0;
		i++;
	}
	system("pause > nul");
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

bool runPhase(players *players, array *played, array *run, array *winners)
{
	int move, arrive;
	bool flag;
	move = 0;
	flag = 0;

	//spostamento lepre
	if ( (arrCountX(played, HARE) > 0  && arrCountX(played, HARE) <= 4)
			&& ( run->d[HARE] <= run->d[WOLF] || run->d[HARE] <= run->d[FOX] || run->d[HARE] <= run->d[TORTOISE] || run->d[HARE] <= run->d[LAMB] )
			&& run->d[HARE] != 11){

		move = 2;
		arrive = move + run->d[HARE];
		while ( run->d[HARE] != arrive && run->d[HARE] != 11){
			Sleep(200);
			run->d[HARE]++;
			printAnimal(HARE, run->d[HARE]);
		}
	}
	//spostamento lupo
	if ( ( arrCountX( played, WOLF) == 1 || arrCountX(played, WOLF) == 2 )  && run->d[WOLF] != 11){
		move = 1;
		arrive = move + run->d[WOLF];

		while ( run->d[WOLF] != arrive && run->d[WOLF] != 11){
			Sleep(200);
			run->d[WOLF] ++;
			printAnimal(WOLF, run->d[WOLF] );
		}

	} else if ( ( arrCountX(played, WOLF) == 3 || arrCountX(played, WOLF)  == 4 ) && run->d[WOLF] != 11){
		move = arrCountX(played, WOLF) - 1;
		arrive = move + run->d[WOLF];

		while ( run->d[WOLF] != arrive && run->d[WOLF] != 11 ){
			Sleep(200);
			run->d[WOLF] ++;
			printAnimal(WOLF, run->d[WOLF] );

		}
	}

	//spostamento tartaruga
	if ( ( arrCountX(played, TORTOISE) >= 0  &&  arrCountX(played, TORTOISE) <= 3 ) && run->d[TORTOISE] != 11 ) {
		move = 1;
		arrive = move + run->d[TORTOISE];
		while ( run->d[TORTOISE] != arrive && run->d[TORTOISE] != 11){
			Sleep(200);
			run->d[TORTOISE] ++;
			printAnimal(TORTOISE, run->d[TORTOISE] );
		}
	} else if ( arrCountX(played, TORTOISE) == 4 && run->d[TORTOISE] != 11 ){
		move = 2;
		arrive = move + run->d[TORTOISE];
		while ( run->d[TORTOISE] != arrive && run->d[TORTOISE] != 11){
			Sleep(200);
			run->d[TORTOISE] ++;
			printAnimal(TORTOISE, run->d[TORTOISE] );
		}
	}

	//spostamento agnello
	if ( arrCountX(played, LAMB) > 0 && run->d[LAMB] != 11 ) {
		move = arrCountX(played, LAMB) + 1;
		arrive = move + run->d[LAMB];
		while ( run->d[LAMB] != arrive && flag == false && run->d[LAMB] != 11){
			if ((run->d[LAMB] == 7 || run->d[LAMB] == 3))
			{
				flag = true;
			}
			Sleep(200);
			run->d[LAMB] ++;
			printAnimal(LAMB, run->d[LAMB] );

		}
	}

	//spostamento volpe
	if ( arrCountX(played, FOX) > 0 && run->d[FOX] != 11 ) {
		move = arrCountX(played, FOX);
		arrive = move + run->d[FOX];
		while ( run->d[FOX] != arrive && run->d[FOX] != 11 ){
			Sleep(100);
			run->d[FOX]++;
			printAnimal(FOX, run->d[FOX]);
		}
	}

	StandPositions(run, winners);
	if ( arrMaxN(winners) == 3 || arrCountX(winners, 0) == 0 ){
		return true;
	}

	return false;
}


void StandPositions(array *run, array * winners)
{
	int first;

	first = arrMaxN(winners);

	if(run->d[WOLF] == 11 && winners->d[0] == 0 ){
		winners->d[0] = first + 1;
	}
	if(run->d[HARE] == 11 && winners->d[1] == 0){
		winners->d[1] = first + 1;
	}
	if(run->d[TORTOISE] == 11 && winners->d[2] == 0 ){
		winners->d[2] = first + 1;
	}
	if(run->d[LAMB] == 11 && winners->d[3] == 0 ){
		winners->d[3] = first + 1;
	}
	if(run->d[FOX] == 11 && winners->d[4] == 0 ){
		winners->d[4] = first + 1;
	}

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

	system("color f0");

	hidecursor();

	consoleTitle("La Lepre e La Tartaruga");

	return 0;
}
