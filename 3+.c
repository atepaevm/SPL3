#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
#include "3+.h"
size_t gen_push_rbp(char* const ptr)
{
*ptr=0x55;
return 1;
}
size_t gen_mov_rbp_rsp(char* const ptr)
{
*ptr=0x48;
*(ptr+1)=0x89;
*(ptr+2)=0xe5;
return 3;
}
size_t gen_xor_rax_rax(char* const ptr)
{
*ptr=0x48;
*(ptr+1)=0x31;
*(ptr+2)=0xc0;
return 3;
}
size_t gen_add_rax_rdi(char* const ptr)
{
*ptr=0x48;
*(ptr+1)=0x03;
*(ptr+2)=0x07;
return 3;
}
size_t gen_add_rax_rdi_offset(char* const ptr,const int a)
{
int i=a;
int b=0;
int j=3;
int k=0;
char buffer;
char str[7];
str[0]=72;
str[1]=3;
str[2]=-121;
while(i>0)
{
b=i%256;
i/=256;
str[j]=(char)(b);
j++;
}
for(k=3;k<(j+3)/2;k++)
{
buffer=str[k];
str[k]=str[j+3-k-1];
str[j+3-k-1]=buffer;
}
for(i=j;i<7;i++)
{
str[i]=0;
}
memcpy(ptr,str,7);
return 7;
}
size_t gen_mov_rsp_rbp(char* const ptr)
{
*ptr=0x48;
*(ptr+1)=0x89;
*(ptr+2)=0xec;
return 3;
}
size_t gen_pop_rbp(char* const ptr)
{
*ptr=0x5d;
return 1;
}
size_t gen_ret(char* const ptr)
{
*ptr=0xc3;
return 1;
}