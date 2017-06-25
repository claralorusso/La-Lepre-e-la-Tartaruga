#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "gui.h"
#include "globals.h"
#include "tools.h"


/// Definizione della schermata del titolo

static char title[] =
		"\t _             _                                               \n"
		"\t| |           | |                                              \n"
		"\t| |     __ _  | |     ___ _ __  _ __ ___    ___                \n"
		"\t| |    / _` | | |    / _ | '_ \\| '__/ _ \\  / _ \\               \n"
		"\t| |___| (_| | | |___|  __| |_) | | |  __/ |  __/               \n"
		"\t|______\\__,_| |__________| .__/__|  \\___|  \\___|               \n"
		"\t  | |           |__   __|| |    | |                              \n"
		"\t  | |     __ _     | | __ ______| |_ __ _ _ __ _   _  __ _  __ _ \n"
		"\t  | |    / _` |    | |/ _` | '__| __/ _` | '__| | | |/ _` |/ _` |\n"
		"\t  | |___| (_| |    | | (_| | |  | || (_| | |  | |_| | (_| | (_| |\n"
		"\t  |______\\__,_|    |_|\\__,_|_|   \\__\\__,_|_|   \\__,_|\\__, |\\__,_|\n"
		"\t                                                      __/ |    \n"
		"\t                                                     |___/     \n";

/// Menu principale
static char menu_screen[] =
			"\t\t\t1) NUOVA PARTITA\n"
			"\t\t\t2) CARICA PARTITA\n"
			"\t\t\t3) IMPOSTAZIONI\n"
			"\t\t\t4) AIUTO\n"
			"\t\t      ESC) ESCI\n"
			"\n\t\tPREMERE IL TASTO DELLA SCELTA DESIDERATA...\n";

/// Struttura di una carta
static char card[] = ":---:";
static char card_blank[] = "|   |";
static char card_wolf[] = "| W |";
static char card_hare[] = "| H |";
static char card_tortoise[] = "| T |";
static char card_lamb[] = "| L |";
static char card_fox[] = "| F |";

/// Legenda
static char reference1[] = "W - Lupo";
static char reference2[] = "H - Lepre";
static char reference3[] = "T - Tartaruga";
static char reference4[] = "L - Agnello";
static char reference5[] = "F - Volpe";

/// Percorso
static char field[] =
YELLOW"           :______::______::______::______::____:\n"
"      "RED"START"YELLOW"|      ||      ||      ||   "CYANO"|"YELLOW"  ||    |\n"
"           :______::______::______::___"CYANO"|"YELLOW"__:|    |\n"
"                                           :____:\n"
"                                           :____:\n"
" "RED"E"YELLOW" :______::______::______::______::______:|    |\n"
" "RED"N"YELLOW" |      ||      ||      ||   "CYANO"|"YELLOW"  ||      ||    |\n"
" "RED"D"YELLOW" :______::______::______::___"CYANO"|"YELLOW"__::______::____:\n"BLACK;

/// Comandi
static char commands[] = "      (1 - 6) Selezione Carta (Spazio) Fine Turno (S) Salva          (ESC) Esci";

static char settings_commands[] =
		" ("RED"W - S"BLACK") Sposta Cursore ("RED"A - D"BLACK") Modifica Selezione ("RED"Spazio"BLACK") Salva Modifiche     "
		" ("RED"C"BLACK") Modifica Nome                                                 ("RED"ESC"BLACK") Esci";


static char saveGame_commands[] =  " ("RED"W - S"BLACK") Sposta Cursore ("RED"Spazio"BLACK") Salva ("RED"X"BLACK") Elimina               ("RED"ESC"BLACK") Esci";
static char loadGame_commands[] =  " ("RED"W - S"BLACK") Sposta Cursore ("RED"Spazio"BLACK") Carica ("RED"X"BLACK") Elimina              ("RED"ESC"BLACK") Esci";

static movepos animals_position;


void printRef()
{
	GotoXY(60, 1);
	printf(BLU"Legenda:"BLACK);
	GotoXY(60, 2);
	printf("%s",reference1);
	GotoXY(60, 3);
	printf("%s",reference2);
	GotoXY(60, 4);
	printf("%s",reference3);
	GotoXY(60, 5);
	printf("%s",reference4);
	GotoXY(60, 6);
	printf("%s",reference5);
}

void printStaticsSettings()
{
	int i;
	GotoXY(25, 1);
	printf("LA LEPRE E LA TARTARUGA");
	GotoXY(30, 3);
	printf(BLU"IMPOSTAZIONI:"BLACK);
	GotoXY(0, 22);
	i = 0;
	while (i < 80){
		printf("-");
		i++;
	}

	GotoXY(0, 23);
	printf("%s",settings_commands);
}


void printStaticsSaveGame()
{
	int i;
	GotoXY(25, 1);
	printf("LA LEPRE E LA TARTARUGA");
	GotoXY(30, 3);
	printf(BLU"SALVA PARTITA:"BLACK);

	GotoXY(25, 6);
	i = 0;
	while ( i < 5){
		GotoXY(25, 6 + i);
		printf("(SLOT)");
		i++;
	}
	GotoXY(0, 23);
	i = 0;
	while (i < 80){
		printf("-");
		i++;
	}

	GotoXY(0, 24);
	printf("%s",saveGame_commands);
}

void printStaticsLoadGame()
{
	int i;
	GotoXY(25, 1);
	printf("LA LEPRE E LA TARTARUGA");
	GotoXY(30, 3);
	printf(BLU"CARICA PARTITA:"BLACK);

	GotoXY(25, 6);
	i = 0;
	while ( i < 5){
		GotoXY(25, 6 + i);
		printf("(SLOT)");
		i++;
	}
	GotoXY(0, 23);
	i = 0;
	while (i < 80){
		printf("-");
		i++;
	}

	GotoXY(0, 24);
	printf("%s",loadGame_commands);
}

void printStatics()
{
	int i;
	GotoXY(25, 0);
	printf("LA LEPRE E LA TARTARUGA");
	GotoXY(0, 23);
	i = 0;
	while (i < 80){
		printf("-");
		i++;
	}

	GotoXY(0, 24);
	printf("%s",commands);
}

void printTitle(void)
{
	printf("%s", title);
}

void printMenu(void)
{
	printf("%s", menu_screen);
}

void printBet(array *bets)
{
	int i;

	GotoXY(52, 18);
	printf("Carte Scommessa");

	GotoXY(52, 19);
	i = 0;
	while ( i < bets->n ){
		printf("%s ", card);
		i++;
	}
	GotoXY(52, 20);
	i = 0;
	while ( i < bets->n ){

		if ( bets->d[i] == WOLF){

			printf("%s ", card_wolf);
		} else if ( bets->d[i] == HARE ) {

			printf("%s ", card_hare);
		} else if ( bets->d[i] == TORTOISE ){

			printf("%s ", card_tortoise);
		} else if ( bets->d[i] == LAMB ){

			printf("%s ", card_lamb);
		} else if ( bets->d[i] == FOX ){

			printf("%s ", card_fox);
		} else if ( bets->d[i] == 0 ){
			printf("%s ", card_blank);
		}
		i++;
	}
	GotoXY(52, 21);
	i = 0;
	while ( i < bets->n ){
		printf("%s ", card);
		i++;
	}
}

void printTurn(char name[], bool ia)
{
	GotoXY(15, 16);
	printf("                                                        ");
	GotoXY(15, 16);
	printf(GREEN"Sta giocando: %s", name);
	if ( ia == true ){
		GotoXY(43, 16);
		printf("(I.A.)");
	}
	printf( BLACK );
}

void printHand(array *cards)
{
	int i;

	GotoXY(8, 18);
	printf(GREEN"Carte Corsa"BLACK);
	GotoXY(8, 19);
	i = 0;
	while ( i < cards->n ){
		printf("%s ", card);
		i++;
	}
	GotoXY(8, 20);
	i = 0;
	while ( i < cards->n ){

		if ( cards->d[i] == WOLF){

			printf("%s ", card_wolf);
		} else if ( cards->d[i] == HARE ) {

			printf("%s ", card_hare);
		} else if ( cards->d[i] == TORTOISE ){

			printf("%s ", card_tortoise);
		} else if ( cards->d[i] == LAMB ){

			printf("%s ", card_lamb);
		} else if ( cards->d[i] == FOX ){

			printf("%s ", card_fox);
		} else if ( cards->d[i] == 0 ){
			printf("%s ", card_blank);
		}
		i++;
	}
	GotoXY(8, 21);
	i = 0;
	while ( i < cards->n ){
		printf("%s ", card);
		i++;
	}
}

void printPlayed(array *cards)
{
	int i;

	GotoXY(5, 11);
	printf(GREEN"Carte Giocate"BLACK);
	GotoXY(5, 12);
	i = 0;
	while ( i < cards->n ){
		printf("%s ", card);
		i++;
	}
	GotoXY(5, 13);
	i = 0;
	while ( i < cards->n ){

		if ( cards->d[i] == WOLF){

			printf("%s ", card_wolf);
		} else if ( cards->d[i] == HARE ) {

			printf("%s ", card_hare);
		} else if ( cards->d[i] == TORTOISE ){

			printf("%s ", card_tortoise);
		} else if ( cards->d[i] == LAMB ){

			printf("%s ", card_lamb);
		} else if ( cards->d[i] == FOX ){

			printf("%s ", card_fox);
		} else if ( cards->d[i] == 0 ){
			printf("%s ", card_blank);
		}
		i++;
	}
	GotoXY(5, 14);
	i = 0;
	while ( i < cards->n ){
		printf("%s ", card);
		i++;
	}
}

void printRoute(void)
{
	GotoXY(0, 1);
	printf("%s", field);

}

void printPointer(int pos, bool flag)
{
	coord * pointers;

	pointers = malloc(7 * sizeof(coord));

	pointers[0].x = 10;
	pointers[1].x = 16;
	pointers[2].x = 22;
	pointers[3].x = 28;
	pointers[4].x = 34;
	pointers[5].x = 40;
	pointers[6].x = 46;

	pointers[0].y = 22;
	pointers[1].y = 22;
	pointers[2].y = 22;
	pointers[3].y = 22;
	pointers[4].y = 22;
	pointers[5].y = 22;
	pointers[6].y = 22;


	GotoXY(pointers[pos].x, pointers[pos].y);
	if ( flag == false){
		printf(GREEN);
		putchar('^');
		printf(BLACK);
	} else if ( flag == true ){

		putchar(' ');
	}



}
int printAnimal(int animal, int pos)
{
	//if (pos == 0){
		//GotoXY(animals_position.animals[0].xy[pos].x, animals_position.animals[0].xy[pos].y);
		//putch('W');
		//GotoXY(animals_position.animals[1].xy[pos].x, animals_position.animals[1].xy[pos].y);
		//putch('H');
		//GotoXY(animals_position.animals[2].xy[pos].x, animals_position.animals[2].xy[pos].y);
		//putch('T');
		//GotoXY(animals_position.animals[3].xy[pos].x, animals_position.animals[3].xy[pos].y);
		//putch('L');
		//GotoXY(animals_position.animals[4].xy[pos].x, animals_position.animals[4].xy[pos].y);
		//putch('F');
	//} else {
		if (animal == WOLF){
			GotoXY(animals_position.animals[0].xy[pos].x, animals_position.animals[0].xy[pos].y);
			putch('W');
			GotoXY(animals_position.animals[0].xy[pos - 1].x, animals_position.animals[0].xy[pos - 1].y);
			putch(' ');
		}
		if (animal == HARE){
			GotoXY(animals_position.animals[1].xy[pos].x, animals_position.animals[1].xy[pos].y);
			putch('H');
			GotoXY(animals_position.animals[1].xy[pos - 1].x, animals_position.animals[1].xy[pos - 1].y);
			putch(' ');
		}
		if (animal == TORTOISE){
			GotoXY(animals_position.animals[2].xy[pos].x, animals_position.animals[2].xy[pos].y);
			putch('T');
			GotoXY(animals_position.animals[2].xy[pos - 1].x, animals_position.animals[2].xy[pos - 1].y);
			putch(' ');
		}
		if (animal == LAMB){
			GotoXY(animals_position.animals[3].xy[pos].x, animals_position.animals[3].xy[pos].y);
			putch('L');
			GotoXY(animals_position.animals[3].xy[pos -1].x, animals_position.animals[3].xy[pos - 1].y);
			putch(' ');
		}
		if (animal == FOX){
			GotoXY(animals_position.animals[4].xy[pos].x, animals_position.animals[4].xy[pos].y);
			putch('F');
			GotoXY(animals_position.animals[4].xy[pos - 1].x, animals_position.animals[4].xy[pos - 1].y);
			putch(' ');
		}
	//}

return 0;
}

void allocPositions()
{
	int i;

	animals_position.animals = malloc( 5 * sizeof(positions) );
	i = 0;
	while(i < 5){
		animals_position.animals[i].xy = malloc( 12 * sizeof(coord) );
		i++;
	}
}

void setPositions()
{
	allocPositions();

	/* Posizioni Lupo*/
	//start
	animals_position.animals[WOLF - 1].xy[0].x = 3;
	animals_position.animals[WOLF - 1].xy[0].y = 0;
	// Posizione 1
	animals_position.animals[WOLF - 1].xy[1].x = 12;
	animals_position.animals[WOLF - 1].xy[1].y = 2;
	// Posizione 2
	animals_position.animals[WOLF - 1].xy[2].x = 20;
	animals_position.animals[WOLF - 1].xy[2].y = 2;
	// Posizione 3
	animals_position.animals[WOLF - 1].xy[3].x = 28;
	animals_position.animals[WOLF - 1].xy[3].y = 2;
	// Posizione 4
	animals_position.animals[WOLF - 1].xy[4].x = 36;
	animals_position.animals[WOLF - 1].xy[4].y = 2;
	// Posizione 5
	animals_position.animals[WOLF - 1].xy[5].x = 44;
	animals_position.animals[WOLF - 1].xy[5].y = 2;
	// Posizione 6
	animals_position.animals[WOLF - 1].xy[6].x = 44;
	animals_position.animals[WOLF - 1].xy[6].y = 6;
	// Posizione 7
	animals_position.animals[WOLF - 1].xy[7].x = 36;
	animals_position.animals[WOLF - 1].xy[7].y = 7;
	// Posizione 8
	animals_position.animals[WOLF - 1].xy[8].x = 28;
	animals_position.animals[WOLF - 1].xy[8].y = 7;
	// Posizione 9
	animals_position.animals[WOLF - 1].xy[9].x = 20;
	animals_position.animals[WOLF - 1].xy[9].y = 7;
	// Posizione 10
	animals_position.animals[WOLF - 1].xy[10].x = 12;
	animals_position.animals[WOLF - 1].xy[10].y = 7;
	// Posizione 11
	animals_position.animals[WOLF - 1].xy[11].x = 4;
	animals_position.animals[WOLF - 1].xy[11].y = 7;

	/* Posizioni Lepre*/
	//start
	animals_position.animals[HARE - 1].xy[0].x = 3;
	animals_position.animals[HARE - 1].xy[0].y = 1;
	// Posizione 1
	animals_position.animals[HARE - 1].xy[1].x = 13;
	animals_position.animals[HARE - 1].xy[1].y = 2;
	// Posizione 2
	animals_position.animals[HARE - 1].xy[2].x = 21;
	animals_position.animals[HARE - 1].xy[2].y = 2;
	// Posizione 3
	animals_position.animals[HARE - 1].xy[3].x = 29;
	animals_position.animals[HARE - 1].xy[3].y = 2;
	// Posizione 4
	animals_position.animals[HARE - 1].xy[4].x = 37;
	animals_position.animals[HARE - 1].xy[4].y = 2;
	// Posizione 5
	animals_position.animals[HARE - 1].xy[5].x = 45;
	animals_position.animals[HARE - 1].xy[5].y = 2;
	// Posizione 6
	animals_position.animals[HARE - 1].xy[6].x = 45;
	animals_position.animals[HARE - 1].xy[6].y = 6;
	// Posizione 7
	animals_position.animals[HARE - 1].xy[7].x = 37;
	animals_position.animals[HARE - 1].xy[7].y = 7;
	// Posizione 8
	animals_position.animals[HARE - 1].xy[8].x = 29;
	animals_position.animals[HARE - 1].xy[8].y = 7;
	// Posizione 9
	animals_position.animals[HARE - 1].xy[9].x = 21;
	animals_position.animals[HARE - 1].xy[9].y = 7;
	// Posizione 10
	animals_position.animals[HARE - 1].xy[10].x = 13;
	animals_position.animals[HARE - 1].xy[10].y = 7;
	// Posizione 11
	animals_position.animals[HARE - 1].xy[11].x = 5;
	animals_position.animals[HARE - 1].xy[11].y = 7;

	/* Posizioni Tartaruga*/
	//start
	animals_position.animals[TORTOISE - 1].xy[0].x = 3;
	animals_position.animals[TORTOISE - 1].xy[0].y = 2;
	// Posizione 1
	animals_position.animals[TORTOISE - 1].xy[1].x = 14;
	animals_position.animals[TORTOISE - 1].xy[1].y = 2;
	// Posizione 2
	animals_position.animals[TORTOISE - 1].xy[2].x = 22;
	animals_position.animals[TORTOISE - 1].xy[2].y = 2;
	// Posizione 3
	animals_position.animals[TORTOISE - 1].xy[3].x = 30;
	animals_position.animals[TORTOISE - 1].xy[3].y = 2;
	// Posizione 4
	animals_position.animals[TORTOISE - 1].xy[4].x = 38;
	animals_position.animals[TORTOISE - 1].xy[4].y = 2;
	// Posizione 5
	animals_position.animals[TORTOISE - 1].xy[5].x = 46;
	animals_position.animals[TORTOISE - 1].xy[5].y = 2;
	// Posizione 6
	animals_position.animals[TORTOISE - 1].xy[6].x = 46;
	animals_position.animals[TORTOISE - 1].xy[6].y = 6;
	// Posizione 7
	animals_position.animals[TORTOISE - 1].xy[7].x = 38;
	animals_position.animals[TORTOISE - 1].xy[7].y = 7;
	// Posizione 8
	animals_position.animals[TORTOISE - 1].xy[8].x = 30;
	animals_position.animals[TORTOISE - 1].xy[8].y = 7;
	// Posizione 9
	animals_position.animals[TORTOISE - 1].xy[9].x = 22;
	animals_position.animals[TORTOISE - 1].xy[9].y = 7;
	// Posizione 10
	animals_position.animals[TORTOISE - 1].xy[10].x = 14;
	animals_position.animals[TORTOISE - 1].xy[10].y = 7;
	// Posizione 11
	animals_position.animals[TORTOISE - 1].xy[11].x = 6;
	animals_position.animals[TORTOISE - 1].xy[11].y = 7;

	/* Posizioni Lepre*/
	//start
	animals_position.animals[LAMB - 1].xy[0].x = 3;
	animals_position.animals[LAMB - 1].xy[0].y = 3;
	// Posizione 1
	animals_position.animals[LAMB - 1].xy[1].x = 15;
	animals_position.animals[LAMB - 1].xy[1].y = 2;
	// Posizione 2
	animals_position.animals[LAMB - 1].xy[2].x = 23;
	animals_position.animals[LAMB - 1].xy[2].y = 2;
	// Posizione 3
	animals_position.animals[LAMB - 1].xy[3].x = 31;
	animals_position.animals[LAMB - 1].xy[3].y = 2;
	// Posizione 4
	animals_position.animals[LAMB - 1].xy[4].x = 40;
	animals_position.animals[LAMB - 1].xy[4].y = 2;
	// Posizione 5
	animals_position.animals[LAMB - 1].xy[5].x = 47;
	animals_position.animals[LAMB - 1].xy[5].y = 2;
	// Posizione 6
	animals_position.animals[LAMB - 1].xy[6].x = 47;
	animals_position.animals[LAMB - 1].xy[6].y = 6;
	// Posizione 7
	animals_position.animals[LAMB - 1].xy[7].x = 39;
	animals_position.animals[LAMB - 1].xy[7].y = 7;
	// Posizione 8
	animals_position.animals[LAMB - 1].xy[8].x = 32;
	animals_position.animals[LAMB - 1].xy[8].y = 7;
	// Posizione 9
	animals_position.animals[LAMB - 1].xy[9].x = 23;
	animals_position.animals[LAMB - 1].xy[9].y = 7;
	// Posizione 10
	animals_position.animals[LAMB - 1].xy[10].x = 15;
	animals_position.animals[LAMB - 1].xy[10].y = 7;
	// Posizione 11
	animals_position.animals[LAMB - 1].xy[11].x = 7;
	animals_position.animals[LAMB - 1].xy[11].y = 7;


	/* Posizioni Volpe*/
	//start
	animals_position.animals[FOX - 1].xy[0].x = 3;
	animals_position.animals[FOX - 1].xy[0].y = 4;
	// Posizione 1
	animals_position.animals[FOX - 1].xy[1].x = 16;
	animals_position.animals[FOX - 1].xy[1].y = 2;
	// Posizione 2
	animals_position.animals[FOX - 1].xy[2].x = 24;
	animals_position.animals[FOX - 1].xy[2].y = 2;
	// Posizione 3
	animals_position.animals[FOX - 1].xy[3].x = 32;
	animals_position.animals[FOX - 1].xy[3].y = 2;
	// Posizione 4
	animals_position.animals[FOX - 1].xy[4].x = 41;
	animals_position.animals[FOX - 1].xy[4].y = 2;
	// Posizione 5
	animals_position.animals[FOX - 1].xy[5].x = 46;
	animals_position.animals[FOX - 1].xy[5].y = 3;
	// Posizione 6
	animals_position.animals[FOX - 1].xy[6].x = 46;
	animals_position.animals[FOX - 1].xy[6].y = 7;
	// Posizione 7
	animals_position.animals[FOX - 1].xy[7].x = 40;
	animals_position.animals[FOX - 1].xy[7].y = 7;
	// Posizione 8
	animals_position.animals[FOX - 1].xy[8].x = 33;
	animals_position.animals[FOX - 1].xy[8].y = 7;
	// Posizione 9
	animals_position.animals[FOX - 1].xy[9].x = 24;
	animals_position.animals[FOX - 1].xy[9].y = 7;
	// Posizione 10
	animals_position.animals[FOX - 1].xy[10].x = 16;
	animals_position.animals[FOX - 1].xy[10].y = 7;
	// Posizione 11
	animals_position.animals[FOX - 1].xy[11].x = 8;
	animals_position.animals[FOX - 1].xy[11].y = 7;

	return ;
}

void playerErrors()
{
	GotoXY(60, 13);
	printf(RED"Non puoi giocare");
	GotoXY(60, 14);
	printf("  questa carta!"BLACK);

	Sleep(500);
	GotoXY(60, 13);
	printf("                ");
	GotoXY(60, 14);
	printf("                ");

	return;
}

void drawSquare(coord angle1, coord angle2)
{
	int row;
	int columns;
	int i;

	row = angle2.x - angle1.x;
	columns = angle2.y - angle1.y;
	// riga superiore
	i = 0;
	while ( i < row ){
		GotoXY( angle1.x + i, angle1.y );
		putch('-');
		i++;
	}
	// riga inferiore
	i = 0;
	while ( i < row ){
		GotoXY( angle1.x + i, angle2.y );
		putch('-');
		i++;
	}

	// colonna sinistra
	i = 0;
	while ( i <= columns ){
		GotoXY( angle1.x, angle1.y + i );
		putch('|');
		i++;
	}
	// colonna destra
	i = 0;
	while ( i <= columns ){
		GotoXY( angle2.x, angle1.y + i );
		putch('|');
		i++;
	}

	return;
}

void printScore(players *p, array *order)
{
	int i;
	coord angle1, angle2, start;

	start.x = 25;
	start.y = 10;

	angle1.x = start.x - 5;
	angle1.y = start.y - 2;

	angle2.x = start.x + 31;
	angle2.y = start.y + 8;

	GotoXY(26, 1);
	printf("LA LEPRE E LA TARTARUGA");

	GotoXY(33, start.y - 3);
	printf(GREEN"CLASSIFICA");

	GotoXY(start.x, start.y);
	printf("%-15s %-5s %-5s","Giocatore", "Tipo", "Punti"BLACK );

	GotoXY(15, angle2.y + 3);
	printf("PARTITA TERMINATA, PREMI UN TASTO PER TORNARE AL MENU");

	drawSquare(angle1, angle2);
	i = 0;

	while ( i < p->n_players){

		GotoXY(start.x, (start.y + 2) + i);
		if (p->player[ order->d[i] ].ai == true){
			printf("%-15s %-5s %-2d", p->player[ order->d[i] ].name,"I.A.", p->player[ order->d[i] ].score );
		} else if ( p->player[ order->d[i] ].ai == false){
			printf("%-15s %-5s %-2d", p->player[ order->d[i] ].name,"Umano", p->player[ order->d[i] ].score );
		}

		i++;
	}

	return;
}
// Gestisce il movimento di un cursore su una lista di max elementi
// input = input inserito dall'utente, start = coordinate di partenza,
// option = variabile che indica l'elemento a cui si punta, max = massimo elementi della lista
int SelectorMovement(char input, coord start, int *option, int max, char confirm)
{
	// funzione viene richiamata per la prima volta, stampa la prima freccia nella prima posizione
	if ( (*option) == 0 && input == 0){
		GotoXY(start.x - 1, start.y  );
		putch('>');
		return 0;
	}

	if ( (input == 'w' || input == 'W') && (*option) > 0){
		(*option)--;
			//stampa il nuovo indicatore
			GotoXY(start.x - 1, start.y + (*option) );
			putch('>');
			//rimuove il vecchio indicatore
			GotoXY(start.x - 1, start.y + (*option) + 1);
			putch(' ');

		}
	if ( (input == 's' || input == 'S') && (*option) < max){
			(*option)++;
			//stampa il nuovo indicatore
			GotoXY(start.x - 1, start.y + (*option) );
			putch('>');
			//rimuove il vecchio indicatore
			GotoXY(start.x - 1, start.y + (*option) - 1);
			putch(' ');
		}
	if ( input == confirm || input == 27 ){
		return 1;
	}

	return 0;
}
