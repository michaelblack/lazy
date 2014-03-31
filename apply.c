#include "apply.h"

// application functions
typedef void * (*zero_arg)();
typedef void * (*one_arg)(void*);
typedef void * (*two_arg) (void *, void *);
typedef void * (*three_arg) (void *, void *, void *);
typedef void * (*four_arg) (void *, void *, void *, void *);
typedef void * (*five_arg) (void *, void *, void *, void *, void *);
typedef void * (*six_arg) (void *, void *, void *, void *, void *, void *);
typedef void * (*seven_arg) (void *, void *, void *, void *, void *, void *, void *);
typedef void * (*eight_arg) (void *, void *, void *, void *, void *, void *, void *, void *);
typedef void * (*nine_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *);

void * apply0(void * f, void ** args) {
  return ((zero_arg)f)();
}

void * apply1(void * f, void ** args) {
  return ((one_arg)f)(args[0]);
}

void * apply2(void * f, void ** args) {
  return ((two_arg)f)(args[0], args[1]);
}

void * apply3(void * f, void ** args) {
  return ((three_arg)f)(args[0], args[1], args[2]);
}

void * apply4(void * f, void ** args) {
  return ((four_arg)f)(args[0], args[1], args[2], args[3]);
}

void * apply5(void * f, void ** args) {
  return ((five_arg)f)(args[0], args[1], args[2], args[3], args[4]);
}

void * apply6(void * f, void ** args) {
  return ((six_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5]);
}

void * apply7(void * f, void ** args) {
  return ((seven_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
}

void * apply8(void * f, void ** args) {
  return ((eight_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
}

void * apply9(void * f, void ** args) {
  return ((nine_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
}
