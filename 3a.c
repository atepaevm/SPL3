#include <stdio.h>
int array[] = { 1, 2, 3, 4, 5,6,7,8,9,10};
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
	int value = sum(array, sizeof(array) / sizeof(int));
	printf("%d \n", value);
	return 0;
}