#include <sys/mman.h>
#include <stdio.h>
#include <malloc.h>
#include "JIT_func.h"

int mul (int a, int b, int c){
	printf("%d %d %d\n",a,b,c);
    return a * b * c;
}

int main(){

    int a[] = {2};
    void *ptr = replace(mul, a, 1);
    int(*fptr)(int, int) = ptr;
    printf("%d\n", fptr(3, 10));
    return 0;
}
