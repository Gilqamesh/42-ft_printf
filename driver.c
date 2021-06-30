#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	ft_printf("%0*i\n", -7, -54);
	printf("%0*i\n", -7, -54);
	return (0);
}
