#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ia.h"

int betcard()
{
	srand(time(NULL));

	return ( rand() % 7 );
}

int iamain(array *cards, array *played_cards, int betcard1, int betcard2)
{
	aiturn turn;
	turn.pos = arrInit(&turn.pos, MAX_TURN);
	turn.pos = arrLoad(&turn.pos, -1);

	int i, j, sum1, sum2, temp;

	sum1 = arrCountX(cards, betcard1);
	sum2 = arrCountX(cards, betcard2);

	if ( sum1 == 0 && sum2 == 0){
		temp = rand() & 6;
		turn.pos.d[0] = temp;
		turn.choice = cards->d[temp];

	} else if (sum1 >= sum2 ){
		turn.choice = betcard1;
		i = 0;
		j = 0;
		while ( i < MAX_CARDS && j < MAX_TURN){
			if ( cards->d[i] == betcard1 ){

				turn.pos.d[j] = i;
				j++;
			}
			i++;
		}
	} else if (sum1 < sum2 ){

		turn.choice = betcard2;
		i = 0;
		j = 0;
		while ( i < MAX_CARDS && j < MAX_TURN){
			if ( cards->d[i] == betcard2 ){
				turn.pos.d[j] = i;
				j++;
			}
			i++;
		}
	}
	while(arrCountX(played_cards, turn.choice) >= 4){

		check(&turn, cards);

	}
	final_check( &turn, played_cards, cards, arrCountNotX(played_cards, 0) );
return 0;
}

int check(aiturn *turn, array *cards)
{
	int i, j;
	i = 0;
	j = 0;
	while ( i < MAX_CARDS && j < MAX_TURN){
		if ( cards->d[i] != turn->choice ){
			turn->choice = cards->d[i];
			j = MAX_TURN;
		}
		i++;
	}
	i = 0;
	j = 0;
	while ( i < MAX_CARDS && j < MAX_TURN){
		if ( cards->d[i] == turn->choice ){

			turn->pos.d[j] = i;
			j++;
		}
		i++;
	}

		return 0;
}


int final_check(aiturn *turn, array *played, array *cards, int n_played )
{
	int i, j;

	if ( n_played != MAX_PLAYED_CARDS ){
		i = 0;
		while ( i < MAX_TURN ){
			j = 0;
			while ( j < MAX_PLAYED_CARDS){

				if ( played->d[j] == 0 && arrCountX(played, turn->choice ) < MAX_TURN && turn->pos.d[i] != -1 ){

					played->d[j] = cards->d[ turn->pos.d[i] ];

					cards->d[ turn->pos.d[i] ] = 0;

					j = MAX_PLAYED_CARDS;

				} else {
				j++;
				}
			}
			i++;
		}

	}
	return 0;
}




