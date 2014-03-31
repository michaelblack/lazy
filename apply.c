#include <stdio.h>
#include <stdlib.h>
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
typedef void * (*ten_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
typedef void * (*eleven_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
typedef void * (*twelve_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
typedef void * (*thirteen_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
typedef void * (*fourteen_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
typedef void * (*fifteen_arg) (void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);

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

void * apply10(void * f, void ** args) {
  return ((ten_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
}

void * apply11(void * f, void ** args) {
  return ((eleven_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10]);
}

void * apply12(void * f, void ** args) {
  return ((twelve_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11]);
}

void * apply13(void * f, void ** args) {
  return ((thirteen_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12]);
}

void * apply14(void * f, void ** args) {
  return ((fourteen_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13]);
}

void * apply15(void * f, void ** args) {
  return ((fifteen_arg)f)(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14]);
}

void * (*apply(int arity))(void *, void **) {
  
  switch(arity) {
  case 0:
    return &apply0;
  case 1:
    return &apply1;
  case 2:
    return &apply2;
  case 3:
    return &apply3;
  case 4:
    return &apply4;
  case 5:
    return &apply5;
  case 6:
    return &apply6;
  case 7:
    return &apply7;
  case 8:
    return &apply8;
  case 9:
    return &apply9;
  case 10:
    return &apply10;
  case 11:
    return &apply11;
  case 12:
    return &apply12;
  case 13:
    return &apply13;
  case 14:
    return &apply14;
  case 15:
    return &apply15;
  default:
    printf("apply: %d arguments unsupported, apply only supports 0-%d arguments.\n", arity, APPLY_MAX);
    exit(1);
  }
}
