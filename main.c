#include <stdio.h>
#include <stdlib.h>

#include "init.h"

int main() { //usunac ten main bo to tylko aby pokazac ze dziala init.h
	graph_t* gr = graph_init(4,5,5,10);
	for(int i = 0; i < 20; i++) {
		printf("%i     ", gr[i].nmb_edg);
		for(int j = 0; j < 4; j++) {
			if(gr[i].edg[j] != NULL)
				printf("%i: %f ", gr[i].edg[j]->node, gr[i].val_edg[j]);
		}
		printf("\n");
	}


	graph_free(&gr, 4, 5);


	return 0;
}
