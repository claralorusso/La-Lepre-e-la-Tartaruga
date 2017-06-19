#include "error_msg.h"
#include <stdio.h>

static char error_generic[] = "Ops, qualcosa e' andato storto :(\nPremere un tasto qualsiai per terminare.";

void printErrorGeneric(void)
{
	printf("%s", error_generic);

}
