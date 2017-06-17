#include <stdlib.h>
#include <stdio.h>
#include "arrays.h"
//#include "tools.h"

/// Inizializza l'array di dimensioni n
array arrInit(array *arr, int n)
{
	arr->d = malloc( n * sizeof(int) );
	arr->n = n;

	return *arr;
}

/// Inserisce il valore x in tutti gli elementi dell'array
array arrLoad(array *arr, int x)
{
	int i = 0;
	while (  i < arr->n ){
			arr->d[i] = x;
			i++;
	}
	return *arr;

}
/// Cerca l'elemento el nell'array
///Si presuppone un array già inizializzato
int arrSearch(array *arr, int el)
{
	int i = 0;
	while (  i < arr->n ){

		if( arr->d[i] == el){
			return i;
		}
		i++;
		}

	return -1;
}

/// Stampa l'array
/// Si presuppone un array già inizializzato
void arrPrint(array *arr)
{
	int i = 0;
	while (  i < arr->n ){

		printf("%d ", arr->d[i]);
		i++;
	}
	printf("\n" );

	return ;
}

/// Riempie l' array al primo posto disponibile (indicato x) con el
array arrFillavb(array  *arr, int el, int x)
{
	int i;

	i = 0;

	while(i < arr->n)
	{
		if(arr->d[i] == x){
			arr->d[i] = el;
			i = arr->n;
		}else {
			i++;
		}
	}
	return *arr;
}

/// Conta tutti gli elementi diversi da x
int arrCountNotX(array  *arr, int x)
{
	int i, sum;
	sum = 0;
	i=0;

	while(i < arr->n)
	{
		if(arr->d[i] != x){
			sum++;
		}
		i++;
	}
	return sum;
}

/// Conta tutti le carte uguali a x
int arrCountX(array *arr, int x )
{
	int sum, i;

	sum = 0;
	i = 0;
	while ( i < arr->n ){
		if ( arr->d[i] == x ){
			sum++;
		}
		i++;
	}

	return sum;
}
