#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "bfs.h"

int main(int argc, char **argv)
{
	int height=atoi(argv[1]);
	int width=atoi(argv[2]);
	graph_t* gr=graph_init(height,width,0,1);
	if(gr==NULL)
		return -1;
	graph_print(gr,height,width);
	bfs(gr,height,width);
	graph_free(&gr, height, width);

	return 0;
}

