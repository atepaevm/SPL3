#include <stdio.h>
#include <stdlib.h>
int is_prime(const unsigned long num)
{
	unsigned long i;
	for (i = 2; num >= i*i; i++) 
	{
		if (num%i == 0)
		return 0;
	}
	return 1;
}
int main(int argc, char** argv)
{	
	int num = -1;
	char str[128];
	char* end;
	unsigned long result;	
	scanf("%s", str);
	num = strtoul(str, &end, 10);	
	result = is_prime(num);	
	if(num==0 || str[0]=='-') 
	{
		perror("Incorrect input!");
	}
	else
	{
	if (result)
		{
		puts("yes");
		}
	else{
		puts("no");
		}
	}	
	return 0;
}