#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "init.h"


double losuj(int a, int b) {
	double wylosowana = (double)rand() / RAND_MAX * (b-a) + a;
	return wylosowana;
}
graph_t* graph_read(char *file)
{
	int a,rows,columns;//ilosc wierszy to wysokosc grafu a kolumn jego szerokosc
        FILE *in = fopen (file,"r");
        if(in==NULL)
        {       printf("Nie udalo sie odczytac pliku");
                return NULL;
        }
        if(fscanf(in,"%d %d\n",&rows,&columns)!=2)
	{       printf("Zly format pliku:");
                return NULL;
        }

        graph_t* gr = malloc(sizeof(graph_t) *rows*columns);
        char *str=malloc(sizeof(str)*1000);

        int offset;
        for(int i=0;i<rows*columns;i++)
        {       gr[i].node = i; 
		gr[i].edg = malloc(sizeof(graph_t*) * 4);
                gr[i].val_edg = malloc(sizeof(double) * 4);
                if(fgets(str,1000,in)==NULL)
		{	printf("Nie udalo sie odczytac linii:%d\n",i+2);
	        	return NULL;
		}	
		else
		{	if (str[0] == '\n')
			{	printf("Linia %d jest pusta",i+2);
				return NULL;
			}
                	for(int j=0;j<4;j++)
                	{
	                        gr[i].edg[j] = NULL;
        	                if(sscanf(str," %d :%lf%n",&a,&gr[i].val_edg[j],&offset)==2)
                	        {	if(!(a==i+columns||a==i-columns||a==i+1||a==i-1))
					{	printf("Wezel podany jako %d w linii %d nie moze zostac polaczony z sasiednimi wezlami\n",j+1,i+2);
						return NULL;
					}
					str+= offset;//offset przesuwa wskaznik na str zeby nie czytac w petli linii ciagle od nowa
                        	        gr[i].edg[j]=&gr[a];//wskaznik na wezel o indeksie a 
	                                gr[i].nmb_edg++;
	                        }
			}
		}
	}
	fclose(in);
	return gr;
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

