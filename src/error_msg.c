#include "error_msg.h"
#include <stdio.h>

static char error_generic[] = "Ops, qualcosa e' andato storto :(\nPremere un tasto qualsiai per terminare.";
static char error_load[] = "Errore nel caricare la partita :(\nPremere un tasto qualsiai per terminare.";

void printErrorGeneric(void)
{
	printf("%s", error_generic);

}

void printErrorLoadUnable(void)
{
	printf("%s", error_load);

}
