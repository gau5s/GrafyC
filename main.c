#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "dijkstr.h"

int main(int argc, char **argv)
{

	graph_t* gr=graph_read(argv[1]);
	if(gr==NULL)
		return -1;
	
	graph_print(gr,7,4);

	dijkstra(gr, 28, 0, 7);

	graph_free(&gr, 7, 4);

	return 0;
}

