#include <stdlib.h>
#include <time.h>

#include "init.h"


double losuj(int a, int b) {
	double wylosowana = (double)rand() / RAND_MAX * (b-a) + a;
	return wylosowana;
}


graph_t* graph_init(int height, int width, double a, double b) { // a i b to przedzial losowania <a,b>
	graph_t* graf = malloc(sizeof(graph_t) *height*width);
	int curr_row = 1;//aktualny wiersz
	int curr_col = 1;//  -,,-   kolumna

	srand( time(NULL) );
	
	for(int i = 0; i < height*width; i++) {
		if(curr_col > width) {
			curr_col = 1;
			curr_row++;
		}

		graf[i].node = i;//ktory wezel
		graf[i].nmb_edg = 0;//liczba krawedzi
		graf[i].edg = malloc(sizeof(graph_t*) * 4);//wskazniki do innych wezlow
		graf[i].val_edg = malloc(sizeof(double) * 4);//wartosci krawedzi


		if(i-width >= 0) { //sprawdza czy jest polaczenie w gore
			graf[i].nmb_edg++;
			graf[i].edg[0] = &(graf[i - width]);
			graf[i].val_edg[0] = losuj(a, b);	
		}
		else {
			graf[i].edg[0] = NULL;
			graf[i].val_edg[0] = 0;
		}

		////////////////////////////
		if(i+1 < curr_row * width) { //w prawo
			graf[i].nmb_edg++;
			graf[i].edg[1] = &(graf[i + 1]);
			graf[i].val_edg[1] = losuj(a, b);
		}
		else {
			graf[i].edg[1] = NULL;
			graf[i].val_edg[1] = 0;
		}

		////////////////////////////
		if(i+width < width*height) { //w dol
			graf[i].nmb_edg++;
			graf[i].edg[2] = &(graf[i + width]);
			graf[i].val_edg[2] = losuj(a, b);
		}
		else {
			graf[i].edg[2] = NULL;
			graf[i].val_edg[2] = 0;
		}

		////////////////////////////
		if(i-1 >= (curr_row - 1) * width) { //w lewo
			graf[i].nmb_edg++;
			graf[i].edg[3] = &(graf[i - 1]);
			graf[i].val_edg[3] = losuj(a, b);
		}
		else {
			graf[i].edg[3] = NULL;
			graf[i].val_edg[3] = 0;
		}
		
		curr_col++;

	}
	
	
	return graf;
}

void graph_free(graph_t** graf, int height, int width) {
	for(int i = 0; i < height*width; i++) {
		free( (*graf)[i].edg );
		free( (*graf)[i].val_edg );
	}
	free(*graf);
	*graf = NULL;
} 

