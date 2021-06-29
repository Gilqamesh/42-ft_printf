#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	ft_printf("%.*s\n", -3, 0);
	printf("%.*s\n", -3, 0);

	return (0);
}
