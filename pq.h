#ifndef _PQ_H_
#define _PQ_H_

typedef struct {
	double *q;  // the queue
	int n;      // actual # of doubles in it
	int s;      // it's size
} * pq_t;

pq_t init_pq( int size );

void add_to_pq( pq_t pq, double x );

int not_empty_pq( pq_t pq );

double pop_from_pq( pq_t pq );

void free_pq( pq_t pq );

#endif
