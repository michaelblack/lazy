#ifndef _PAIRS_H
#define _PAIRS_H

typedef struct pair pair;

void * first(pair *);
void * second(pair *);

pair * pairup(void *, void *);

#endif
