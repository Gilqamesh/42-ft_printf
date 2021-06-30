#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	// ft_printf("%-70.193x%-140c%168c%026.51%%0125.119X\n", 1102840003u,-50,-17,3721437512u);
	ft_printf("%168c\n", -17);
	// printf("%-70.193x%-140c%168c%026.51%%0125.119X\n", 1102840003u,-50,-17,3721437512u);
	printf("%168c\n", -17);
	return (0);
}
