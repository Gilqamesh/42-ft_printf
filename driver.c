#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	int n = -123;
	ft_printf("abc %x abc\n", n);
	printf("abc %X abc\n", n);

	return (0);
}
