#include <stdlib.h>
#include "pairs.h"

struct pair {
  void * first;
  void * second;
};

void * first(pair * p) {
  return p->first;
}

void * second(pair * p) {
  return p->second;
}

pair * pairup(void * a, void * b) {
  pair * p = malloc(sizeof(pair));
  p->first = a;
  p->second = b;
  return p;
}
