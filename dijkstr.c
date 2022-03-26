#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "pq.h"
#define SIZE 32

static void dijkstra_print(d_t* dij, int da, int db) {
	int x;
	int i = db;

	printf("Najkrotsza droga z wezla %i do %i:\n", db, da);
	while(dij[i].k != da) {
		printf("%i ", dij[i].k);
		i = dij[i].p;
	}
	printf("%i\n", da);
}

void dijkstra(graph_t* gr, int n, int da, int db) {//n = rows*columns

	d_t dij[n];// tablica odleglosci i poprzednikow (p) od wezla da
	pq_t queue = init_pq(SIZE);

	for(int i = 0; i < n; i++) {
		dij[i].k = i;
		dij[i].p = -1;// ujemne czyli ze nie ma
		if(i == da) {
			dij[i].odl = 0;
			add_to_pq(queue, dij[i]);
		}
		else
			dij[i].odl = 987987978;//////////////////////////
		//add_to_pq(queue, dij[i]);
	}
	
	d_t tmp;
	while( not_empty_pq(queue) ) {
		d_t act = pop_from_pq(queue);
		for(int j = 0; j < 4; j++) {
			if( gr[act.k].edg[j] != NULL ) {
				if( dij[act.k].odl + gr[act.k].val_edg[j] < dij[ gr[act.k].edg[j]->node ].odl ) {
					dij[ gr[act.k].edg[j]->node ].odl = dij[ act.k ].odl + gr[act.k].val_edg[j];
					dij[ gr[act.k].edg[j]->node ].p = dij[act.k].k;
					add_to_pq(queue, dij[gr[act.k].edg[j]->node]);
				}
			}
		}
	}
	dijkstra_print(dij, da, db);
	free(queue);
}
