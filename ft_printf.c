/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:20:43 by edavid            #+#    #+#             */
/*   Updated: 2021/06/27 17:06:27 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_int_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static char	*malloc_conv_spec(char *format, int *format_index)
{
	int		index;
	int		format_len;
	char	*conversion_specifier;
	char	*conversion_end;
	static char	conversion[] = "cspdiuxX%";

	index = 0;
	while (1)
	{
		conversion_end = ft_strchr(format + *format_index, conversion[index]);
		if (conversion_end)
		{
			format_len = conversion_end - (format + *format_index) + 1;
			break ;
		}
		index++;
	}
	conversion_specifier = malloc(format_len + 1);
	index = -1;
	while (++index < format_len)
		conversion_specifier[index] = format[index];
	conversion_specifier[index] = '\0';
	*format_index += format_len;
	return (conversion_specifier);
}

static int	set_flags(char *conv_spec, int *flags, va_list ap, void **arg_pointer)
{
	int		conv_spec_index;
	char	c;

	conv_spec_index = 0;
	c = conv_spec[conv_spec_index];
	while (c == '-' || c == '0')
	{
		if (c == '-')
		{
			flags[0] = 1;
			flags[1] = 0;
		}
		else if (c == '0' && !flags[0])
			flags[1] = 1;
		c = conv_spec[++conv_spec_index];
	}
	while (ft_isdigit(c))
	{
		flags[2] = flags[2] * 10 + c - '0';
		c = conv_spec[++conv_spec_index];
	}
	if (c == '.')
	{
		c = conv_spec[++conv_spec_index];
		if (c == '*')
		{
			flags[3] = -1;
			flags[4] = *(int *)(*arg_pointer);
			*arg_pointer = va_arg(ap, void *);
			conv_spec_index++;
		}
		else
			while (ft_isdigit(c))
			{
				flags[3] = flags[3] * 10 + c - '0';
				c = conv_spec[++conv_spec_index];
			}
	}
	return (conv_spec_index);
}

static void	print_conversion_c(unsigned char c, int *flags)
{
	if (!flags[0] && flags[2])
		while (--(flags[2]) > 0)
			ft_putchar_fd(' ', 1);
	write(1, &c, 1);
}

static void	print_conversion_s(char *str, int *flags)
{
	int	str_len;
	int padding;

	str_len = ft_strlen(str);
	if (flags[3])
	{
		if (flags[3] == -1)
		{
			if (flags[4] < str_len)
				str_len = flags[4];
		}
		else
		{
			if (flags[3] < str_len)
				str_len = flags[4];
		}
	}
	if (flags[2] > str_len)
	{
		if (flags[0])
		{
			while (*str && str_len)
			{
				write(1, *str++, 1);
				str_len--;
			}
			while (str_len--)
				ft_putchar_fd(' ', 1);
		}
		else
		{
			while ((flags[2])-- > str_len)
				ft_putchar_fd(' ', 1);
			while (*str && str_len)
			{
				write(1, *str++, 1);
				str_len--;
			}
		}	
	}
}

static int	print_ltoh(unsigned long n)
{
	static char	hexa[] = "0123456789abcdef";
	int			calls;

	calls = 0;
	if (n < 16)
	{
		write(1, &hexa[n % 16], 1);
		return 1;
	}
	calls = print_ltoh(n / 16) + 1;
	write(1, &hexa[n % 16], 1);
	return (calls);
}

static int	n_of_digitsl()

static void	print_conversion_p(void *arg_pointer, int *flags)
{
	int addr_len;

	
	write(1, "0x", 2);
	print_ltoh((unsigned long)arg_pointer) + 2;
}

static void	print_conversion(char conversion, void *arg_pointer, int *flags)
{
	if (conversion == 'c')
	{
		print_coversion_c(*(unsigned char*)arg_pointer, flags);
	}
	else if (conversion == 's')
	{
		print_conversion_s((char *)arg_pointer, flags);
	}
	else if (conversion == 'p')
	{
		print_conversion_p(arg_pointer, flags);
	}
	else if (conversion == 'd' || conversion == 'i')
	{
		
	}
	else if (conversion == 'u')
	{

	}
	else if (conversion == 'x' || conversion == 'X')
	{
		
	}
}

// %[$][flags][width][.precision][length modifier]conversion
static int	handle_conversion_spec(void **arg_pointer, char *conv_spec, va_list ap)
{
	/*
		convert conv_spec into the expected str that needs to be written to stdout
		return the number of bytes printed.
	*/
	char	c;
	int		conv_spec_index;
	char	*str;
	int		*flags;

	conv_spec_index = 0;
	flags = ft_calloc(5, sizeof(int));
	while (conv_spec[conv_spec_index])
	{
		// Flag char '-' flags[0]
		//
		// The converted value is to be left adjusted on the field
		// boundary.  (The default is right justification.)  The
		// converted value is padded on the right with blanks, rather
		// than on the left with blanks or zeros.  A - overrides a 0
		// if both are given.
		//
		// Flag char '0' flags[1]
		// The value should be zero padded.  For d, i, o, u, x, X, a,
		// A, e, E, f, F, g, and G conversions, the converted value
		// is padded on the left with zeros rather than blanks.  If
		// the 0 and - flags both appear, the 0 flag is ignored.  If
		// a precision is given with a numeric conversion (d, i, o,
		// u, x, and X), the 0 flag is ignored.  For other
		// conversions, the behavior is undefined.
		//
		// Field width: flags[2]
		// An optional decimal digit string (with nonzero first digit)
		// specifying a minimum field width.  If the converted value has
		// fewer characters than the field width, it will be padded with
		// spaces on the left (or right, if the left-adjustment flag has
		// been given).  Instead of a decimal digit string one may write "*"
		// or "*m$" (for some decimal integer m) to specify that the field
		// width is given in the next argument, or in the m-th argument,
		// respectively, which must be of type int.  A negative field width
		// is taken as a '-' flag followed by a positive field width.  In no
		// case does a nonexistent or small field width cause truncation of
		// a field; if the result of a conversion is wider than the field
		// width, the field is expanded to contain the conversion result.
		//
		// Precision: flags[3] (store if there is precision, -1 if *, otherwise
		// the decimal value of the decimal digit string from the argument
		// flags[4] is taken from the argument of printf
		// An optional precision, in the form of a period ('.')  followed by
		// an optional decimal digit string.  Instead of a decimal digit
		// string one may write "*" or "*m$" (for some decimal integer m) to
		// specify that the precision is given in the next argument, or in
		// the m-th argument, respectively, which must be of type int.  If
		// the precision is given as just '.', the precision is taken to be
		// zero.  A negative precision is taken as if the precision were
		// omitted.  This gives the minimum number of digits to appear for
		// d, i, o, u, x, and X conversions, the number of digits to appear
		// after the radix character for a, A, e, E, f, and F conversions,
		// the maximum number of significant digits for g and G conversions,
		// or the maximum number of characters to be printed from a string
		// for s and S conversions.
		//
		// Handle These flags with a function
		// Parameter: conv_spec string, pointer to flags pointer
		// Return: increment conv_spec_index
		// Side effect: set flags pointer
		conv_spec_index += set_flags(conv_spec, flags, ap, arg_pointer);
		
		// Length modifier might not be needed

		// Conversions: cspdiuxX%
		// c: the int argument is converted
        //    to an unsigned char, and the resulting character is
        //    written.
		// d, i: The int argument is converted to signed decimal notation.
        //       The precision, if any, gives the minimum number of digits
        //       that must appear; if the converted value requires fewer
        //       digits, it is padded on the left with zeros.  The default
        //       precision is 1.  When 0 is printed with an explicit
        //       precision 0, the output is empty.
		// s: the const char * argument is
		//    expected to be a pointer to an array of character type
		//    (pointer to a string).  Characters from the array are
		//    written up to (but not including) a terminating null byte
		//    ('\0'); if a precision is specified, no more than the
		//    number specified are written.  If a precision is given, no
		//    null byte need be present; if the precision is not
		//    specified, or is greater than the size of the array, the
		//    array must contain a terminating null byte.
		// p: The void * pointer argument is printed in hexadecimal
		// u, x, X: The unsigned int argument is converted to unsigned decimal (u)
		//	  or unsigned hexadecimal (x or X). The letters abcdef are used for x
		//    conversions; the letters ABCDEF are used for X
		//    conversions.  The precision, if any, gives the minimum
		//    number of digits that must appear; if the converted value
		//    requires fewer digits, it is padded on the left with
		//    zeros.  The default precision is 1.  When 0 is printed
		//    with an explicit precision 0, the output is empty.
		// %: A '%' is written.
		//
		// Handle the conversion with a function
		// Parameter: current character from the conv_spec string, ap of va_list type,
		//				flags pointer
		// Return: nothing
		// Side-effect: writes ap converted to the correct type to stdout
		print_conversion(conv_spec[conv_spec_index++], *arg_pointer, flags);
	}
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
	va_start(ap, format);
	while (format[format_index])
	{
		if (format[format_index] == '%') // start of conversion specification
		{
			if (format[format_index + 1] == '%')
			{
				write(1, "%", 1);
				format_index++;
				continue ;
			}
			arg_pointer = va_arg(ap, void *);
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
			n_of_printed += handle_conversion_spec(&arg_pointer, conversion_specifier, ap);
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
