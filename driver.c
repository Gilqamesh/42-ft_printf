#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	ft_printf("%*s\n", 32, "abc");
	printf("%-32s\n", "abc");
	return (0);
}
