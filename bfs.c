#include <stdlib.h>
#include <stdio.h>
#include "pq.h"
#include "bfs.h"
#include "init.h"

int bfs(graph_t* gr,int height,int width)
{ 
	int i,n=1;
	int* visited = malloc(sizeof(int)*height*width);
	pq_t pq = init_pq( height*width );
	visited[0]=1;
	add_to_pq(pq,0);
	while(not_empty_pq(pq))
	{
		i = pop_from_pq(pq);
		for(int j=0;j<4;j++)
		{
			if(gr[i].edg[j]!=NULL && visited[gr[i].edg[j]->node]!=1)
			{	
                	printf("%d\n",gr[i].edg[j]->node);
			add_to_pq(pq,gr[i].edg[j]->node);	
			visited[gr[i].edg[j]->node]=1;
			n++;
			}
		}
	}
	free_pq( pq );
        free(visited);
	if(n==height*width)
        {
                printf("\nGraf spojny\n");
                return 1;
        }
        else
        {
                printf("\nGraf nie spojny\n");
                return -1;
        }

}
