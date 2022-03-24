#include <stdlib.h>
#include <stdio.h>
#include "pq.h"
#include "bfs.h"
#include "init.h"


int bfs(graph_t* gr,int height,int width)
{ 
	int n=0;
	int* visited = malloc(sizeof(int)*height*width);
	for(int i=0;i<height*width;i++)
	{
		for(int j=0;j<4;j++)
                {
                        if(gr[i].edg[j]!= NULL && visited[gr[i].edg[j]->node]!=1)
                        {
                        visited[gr[i].edg[j]->node]=1;
                        n++;
                        }
                }
	}	
	if(n==height*width)
	{
		printf("\nGraf spojny\n");
		return 1;
	}
	else
		return -1;
	
}
