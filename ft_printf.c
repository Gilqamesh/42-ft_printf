/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:20:43 by edavid            #+#    #+#             */
/*   Updated: 2021/06/27 10:52:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>

static char	*malloc_conv_spec(char *format, int *format_index)
{
	int		index;
	int		format_len;
	char	*conversion_specifier;

	format_len = ft_strlen(format);
	*format_index += format_len;
	conversion_specifier = malloc(format_len + 1);
	index = -1;
	while (++index < format_len)
		conversion_specifier[index] = format[index];
	conversion_specifier[index] = '\0'; 
	return (conversion_specifier);
}

static int	handle_conversion_spec(void *arg_pointer, char *conv_spec)
{
	/*
		convert conv_spec into the expected str that needs to be written to stdout
		return the number of bytes printed.

		
	*/
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		format_index;
	int		n_of_printed;
	char	*conversion_specifier;
	void	*arg_pointer;

	format_index = 0;
	n_of_printed = 0;
	flag_first_convspec = 0;
	va_start(ap, format);
	while (format[format_index])
	{
		if (format[format_index] == '%') // start of conversion specification
		{
			arg_pointer = va_arg(ap, *void);
			format_index++;
			/*
				store conversion specifier in a str and advance the 
				format_index by that much. Advance ap with va_arg as a type of
				void.
			
				handle format specifier in a different function
				Arguments of this function: 
				- argument's value as a void pointer and
				- also takes in as argument a string that is the conversion
				specifier to later determine the type of the arg.
				Returns the number of bytes printed, increment n_of_printed.
				As side-effect it also writes to stdout.
			*/
			// get the str of the conversion specifier via function
			// increase format_index as a side effect
			conversion_specifier = malloc_conv_spec(format,  &format_index);

			// function that handles the format specifier string
			n_of_printed += hadle_conversion_spec(arg_pointer, conversion_specifier);
		}
		else
		{
			write(1, format + format_index++, 1);
			n_of_printed++;
		}
	}
	va_end(ap);
	return (n_of_printed);
}
