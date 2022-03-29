#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "init.h"
#include "dijkstr.h"
#include "bfs.h"
char* help=
	"POMOC:\n:"
	"Najpierw nalezy wczytac graf z pliku lub go wygenerowac\n"
	"Generowanie grafu: -g -a [ilosc wierszy(wysokosc)grafu] -b [ilosc kolumn(szerokosc)grafu]\n"
	"-m [dolny zakres losowanych wartosci(nieujemne)] -n [gorny zakres losowanych wartosci(nieujemne)]\n"
	"Wczytanie grafu z pliku: -i [nazwa pliku]\n"
	"Zapisanie grafu do pliku: -o [nazwa pliku]\n"
	"Sprawdzenie spojnosci grafu: -s\n"
	"Wyznaczenie najkrotszej sciezki algorytmem dijkstry: -d -e[pierwszy wezel] -f [drugi wezel]\n";
int main(int argc, char **argv)
{	graph_t* gr;
	char *fout=NULL;
	char *fin=NULL;
	int opt,height,width,sn,sflag,gflag,pflag,dflag;
	double min,max;
	int fn=-1;

	while ((opt = getopt (argc, argv, "ga:b:m:n:o:i:de:f:sp")) != -1) {
		switch (opt) {
			case 'g':
				gflag=1;
				break;
			case 'a':
				height = atoi(optarg);
				break;
			case 'b':
				width = atoi(optarg);
				break;
			case 'm':
				min = atof(optarg);
				break;
			case 'n':
				max = atof(optarg);
				break;
			case 'o':
				fout = optarg;
				break;
			case 'i':
				fin = optarg;
				break;
			case 'd':
				dflag=1;
				break;
			case 'e':
                                fn = atoi (optarg);
                                break;
                        case 'f':
                                sn = atoi (optarg);
                                break;
			case 's':
				sflag=1;
				break;
			case 'p':
                                pflag=1;
                                break;
			default:
				fprintf (stderr, help, argv[0]);
				exit (EXIT_FAILURE);
		}
	}
	
	if(gflag==1)
	{
		if(height>0 && width>0 && min>=0 && max>0 && max>min)
		{
			graph_t* gr=graph_init(height,width,min,max);
			if(gr==NULL)
				return -1;
			if(pflag==1)
       			{             	
	                       	graph_print(gr,height,width);
       			}
			if(fout!=NULL)
			{
				graph_fwrite(fout,gr,height,width);
			}	
                        if(sflag==1)
                        {
                                bfs(gr,height,width);
                        }
                        if(dflag==1)
                        {	if(fn>=height*width || sn>=height*width)
					printf("Podano wezly wykraczajace poza graf dla algorytmu dijktstry\n");
                               	else
					dijkstra(gr,height*width,fn,sn);
                        }

			graph_free(&gr,height,width);
			return 0;
		}
		else
		{	printf("Podane zle wartosci do generacji grafu\n");
			fprintf (stderr, help, argv[0]);
			return -1;
		}	
		
	}		
	else if(fin!=NULL)
        {
			int *rw,*rh;
                        if(gr==NULL)
                                return -1;
                        FILE *in=fopen(fin,"r");
                        if(fscanf(in,"%d %d",&height,&width)!=2)
                        {       printf("Na poczatku pliku powinny byc podane wymiary grafu\n");
                                return -1;
                        }
			graph_t* gr=graph_read(fin,NULL,NULL);
                        if(pflag==1)
                        {
                                graph_print(gr,height,width);
                        }
                        if(fout!=NULL)
                        {
                                graph_fwrite(fout,gr,height,width);
                        }
			if(sflag==1)
			{
				bfs(gr,height,width);
			}
			if(dflag==1)
                        {       if(fn>=height*width || sn>=height*width)
                                        printf("Podano wezly wykraczajace poza graf");
                                else
					dijkstra(gr,height*width,fn,sn);
		        }
                        graph_free(&gr,height,width);
                        return 0;

	}
	else
	{
		printf("Nalezy podac graf\n");
		fprintf (stderr, help, argv[0]);
		return -1;
	}

	
	return 0;
}

