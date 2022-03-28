#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "dijkstr.h"

#include "bfs.h"


int main(int argc, char **argv)
{	
	int height;
	int width;
	//graph_t* gr=graph_init(height,width,0,1);
	graph_t* gr=graph_read(argv[1], &height, &width);
	if(gr==NULL)
		return -1;
	
	graph_print(gr,height,width);
	
	bfs(gr,height,width);

	dijkstra(gr, height*width, 0, 7);

	graph_free(&gr, height, width);

	return 0;
}

