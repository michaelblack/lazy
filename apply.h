#ifndef _APPLY_H
#define _APPLY_H
#define APPLY_MAX 15

void * apply0(void * f, void ** args);
void * apply1(void * f, void ** args);
void * apply2(void * f, void ** args);
void * apply3(void * f, void ** args);
void * apply4(void * f, void ** args);
void * apply5(void * f, void ** args);
void * apply6(void * f, void ** args);
void * apply7(void * f, void ** args);
void * apply8(void * f, void ** args);
void * apply9(void * f, void ** args);
void * apply10(void * f, void ** args);
void * apply11(void * f, void ** args);
void * apply12(void * f, void ** args);
void * apply13(void * f, void ** args);
void * apply14(void * f, void ** args);
void * apply15(void * f, void ** args);
void * (*apply(int arity))(void * f, void ** args);

#endif
