#include <stdio.h>
#include <stdlib.h>
#include "websignal.h"

void signalHandler(int signalNum)
{
	printf("close the socket\n");
	exit(1);
}
