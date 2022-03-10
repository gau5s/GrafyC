#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"

int main(int argc, char **argv)
{	//main testujący funkcje graf_read

//generowanie grafu
/*	FILE *out = fopen (argv[1],"w");
	graph_t* graf = graph_init(10,10,5,10);
	fprintf(out,"10 10\n");
	for(int i = 0; i < 100; i++) {
		for(int j = 0; j < 4; j++) {
			if(graf[i].edg[j] != NULL)
				fprintf(out,"%i: %f ", graf[i].edg[j]->node, graf[i].val_edg[j]);
		}
		fprintf(out,"\n");
	}
	fclose(out);

*/
	

	graph_t* gr=graph_read(argv[1]);
	if(gr==NULL)
		return -1;
	for(int i = 0; i < 100; i++) {

                for(int j = 0; j < 4; j++) {
                        if(gr[i].edg[j]!= NULL)
                                printf("%i: %f ", gr[i].edg[j]->node, gr[i].val_edg[j]);
                }
                printf("\n");
        }
	graph_free(&gr, 10, 10);
	return 0;
}


	


