#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
int sum(int const* const array, size_t const size) {
	int sum = 0;
	size_t i = 0UL;
	for (i = 0; i<size; i++)
	{
		sum += array[i];
	}
	return sum;
}
int main(int argc, char** argv)
{
	size_t n = 0;
	size_t  i = 0;
	int* array;
	int value;
	if (0 == scanf("%lu", &n))
	{
		perror("Incorrect input");
		return 0;
	}
	array = (int*)malloc(sizeof(int)*n);
	if (NULL == array)
	{
		perror("Incorrect input");
		free(array);
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		if (0 == scanf("%d", &array[i]))
		{
			perror("Incorrect input");
			free(array);
			return 0;
		}
	}
	value = sum(array, n);
	printf("%d \n", value);
	free(array);
	return 0;
}
