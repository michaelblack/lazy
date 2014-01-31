#include "lazy.h"
#include <stdio.h>
#include "pairs.h"

void print_int(void * num);
void * add1(void * n);
void * times2(void * n);
int odd(void * n);
void * add(void * a, void * b);
void * id(void * a);
pair * fibs_unfolder(void * acc)  ;

int main() {

  stream * natural_numbers = iterate(&add1, (void *) 1);
  stream * threes = iterate(&id, (void *) 3);
  stream * fibonaccis = streamcons( (void *) 0,
				    promiseWrap( streamcons( (void *) 1,
							     promiseWrap(
									 unfold(&fibs_unfolder,
										(void *)(pairup((void *) 0,
												(void *) 1)))))));
     
  //prints the first 10 powers of 2
  printf("The first 10 powers of two (testing `iterate`) :\n\t");
  foreach( &print_int, take(10, iterate(&times2, (void *) 1)));
  puts("\n");

  // prints the first 10 even digs
  printf("Mapping f(x) = x*2 across 10 of the natural numbers (testing `map`) :\n\t");
  foreach( &print_int, take( 10, map( &times2, natural_numbers)));
  puts("\n");
  
  //prints the first 10 odd digits
  printf("The first 10 odd numbers (testing `filter`) :\n\t");
  foreach( &print_int, take( 10, filter( &odd, natural_numbers)));
  puts("\n");

  //prints a zip test
  printf("The first 10 of [1,2..] + [3,3..] (testing `zip2`):\n\t");
  foreach( &print_int, take( 10, zip2( &add, natural_numbers, threes)));
  puts("\n");

  //prints the first 10 fibonnaci numbers
  printf("The first 15 fibonacci numbers (testing `unfold`) :\n\t");
  foreach( &print_int, take(15, fibonaccis));
  puts("\n");

}

void print_int(void * num) {
  printf("%d ", (int) num);
}

void * add1(void * n) {
  return (void *)(1 + (int)n);
}

void * times2(void * n) {
  return (void *)(2 * (int) n);
}

int odd(void * n) {
  return ((int)n)%2 != 0;
}

void * add(void * a, void * b) {
  return (void *)((int) a + (int)b);
}

void * id(void * a) {
  return a;
}

pair * fibs_unfolder(void * acc) {
  void * fst = first((pair *)acc);
  void * snd = second((pair *)acc);
  void * added = (void *)((int)fst + (int)snd); 
  return pairup( added,
		 (void *)(pairup(snd, added)));
}
