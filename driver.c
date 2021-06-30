#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	int a = 2;
	int *tmp = &a;
	ft_printf("%2.3p\n", tmp);
	printf("%2.3p\n", tmp);
	return (0);
}
