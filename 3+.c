#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <string.h>
int gen_push_rbp(char* const ptr)
{
char str[]="\x55";
memcpy(ptr,str,1);
return 1;
}
int mov_rbp_rsp(char* const ptr)
{
char str[]="\x48\x89\xe5";
memcpy(ptr,str,3);
return 3;
}
int xor_rax_rax(char* const ptr)
{
char str[]="\x48\x31\xc0";
memcpy(ptr,str,3);
return 3;
}
int add_rax_rdi(char* const ptr)
{
char str[]="\x48\x03\x07";
memcpy(ptr,str,3);
return 3;
}
int add_rax_rdi_offset(char* const ptr,const int a)
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
int mov_rsp_rbp(char* const ptr)
{
char str[]="\x48\x89\xec";
memcpy(ptr,str,3);
return 3;
}
int pop_rbp(char* const ptr)
{
char str[]="\x5d";
memcpy(ptr,str,1);
return 1;
}
int ret(char* const ptr)
{
char str[]="\xc3";
memcpy(ptr,str,1);
return 1;
}
void convert_to_assembler(int* const array,const size_t n)
{
char* ptr;	
int (*sum)(int*);
int i=0;	
ptr=(char*)mmap(NULL, 10, PROT_WRITE|PROT_EXEC, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
sum=(int(*)(int*))(void*)ptr;
ptr+=gen_push_rbp(ptr);
ptr+=mov_rbp_rsp(ptr);
ptr+=xor_rax_rax(ptr);
ptr+=add_rax_rdi(ptr);
for(i=1;i<n;i++)
{
ptr+=add_rax_rdi_offset(ptr,4*i);
}
ptr+=mov_rsp_rbp(ptr);
ptr+=pop_rbp(ptr);
ptr+=ret(ptr);
printf("sum is %i\n",sum(array));
}
int main(int argc, char** argv)
{
int array[]={1,4,7,2,6};
convert_to_assembler(array,5);	
return 0;
}