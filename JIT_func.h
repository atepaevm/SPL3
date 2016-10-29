#include <sys/mman.h>
#include <stdio.h>
#include <malloc.h>

#ifndef JIT_FUNC_H
#define JIT_FUNC_H

char* int_to_LEstr(int a);

#define regc 6

char* strcopy(char*, char*, int);

void* replace(void*, int *, int);

#endif
