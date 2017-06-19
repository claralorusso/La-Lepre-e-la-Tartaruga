#ifndef ARRAYS_H_
#define ARRAYS_H_
#include "tools.h"

typedef struct array{
	int *d;
	int n;
}array;



array arrInit(array *, int);
array arrLoad(array *, int );
int arrSearch(array *, int );
void arrPrint(array *);
int countninarow(array *, int , int );
array arrFillavb(array  *, int , int ); // Inserisce el nella prima posizione disponibile diversa da x
int arrCountNotX(array  *, int ); // Conta tutti gli elementi diversi da x
int arrCountX(array *, int  );// Conta tutti gli elementi uguali x
#endif /* ARRAYS_H_ */
