#include <stdio.h>
#include <stdint.h>

// %zu -> size_t
int	main(void)
{
	printf("Size of int: %zu bytes\n", sizeof(int));
	printf("Size of int32: %zu bytes\n", sizeof(int32_t));
	printf("Size of int64: %zu bytes\n", sizeof(int64_t));
	printf("Size of long: %zu bytes\n", sizeof(long));
	printf("Size of long long: %zu bytes\n", sizeof(long long));
	printf("Size of float: %zu bytes\n", sizeof(float));
}
