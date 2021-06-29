#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	ft_printf("%-*.*s", 7, 3, "yolo");
	printf("%-*.*s", 7, 3, "yolo");
	return (0);
}
