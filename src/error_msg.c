#include "error_msg.h"
#include <stdio.h>

static char error_generic[] = "Ops, qualcosa e' andato storto :(\nPremere un tasto qualsiai per terminare.";

static char error_load[] = "Errore nel caricare la partita :(\nPremere un tasto qualsiai per terminare.";

static char error_save[] = "Errore nel salvare la partita :(\nControlla che la cartella sav sia nella stessa cartella dell'eseguibile\nPremere un tasto qualsiai per terminare.";

static char error_rules[] = "File del regolamento non trovato :(\nPremere un tasto qualsiai per tornare indietro.";
void printErrorGeneric(void)
{
	printf( error_generic);

}

void printErrorLoadUnable(void)
{
	printf(error_load);

}

void printErrorSaveUnable(void)
{
	printf(error_save);

}

void printErrorNoRules(void)
{
	printf(error_rules);

}
