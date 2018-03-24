#include <stdio.h>
#include "GraphTypes.h"
#include "gInterface.h"


int main(void)
{
	Graph G;
	ScanGraphAdjList(&G);
  	printf("Strongly Connected Components:\n");
	SSC(G,PrintElement);
	return 0;
}
