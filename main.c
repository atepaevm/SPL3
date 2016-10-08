#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include "3+.h"
void convert_to_assembler(int* const array,const size_t n)
{
char* ptr;	
int (*sum)(int*);
int i=0;	
ptr=(char*)mmap(NULL, 10, PROT_WRITE|PROT_EXEC, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
sum=(int(*)(int*))(void*)ptr;
ptr+=gen_push_rbp(ptr);
ptr+=gen_mov_rbp_rsp(ptr);
ptr+=gen_xor_rax_rax(ptr);
ptr+=gen_add_rax_rdi(ptr);
for(i=1;i<n;i++)
{
ptr+=gen_add_rax_rdi_offset(ptr,4*i);
}
ptr+=gen_mov_rsp_rbp(ptr);
ptr+=gen_pop_rbp(ptr);
ptr+=gen_ret(ptr);
printf("sum is %i\n",sum(array));
}
int main(int argc, char** argv)
{
int array[]={1,4,7,2,6,45,0,-1};
convert_to_assembler(array,8);	
return 0;
}