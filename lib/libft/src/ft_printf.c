#include "libft.h"

int	ft_print_conversion(char conv, va_list args)
{
	unsigned long int	longint;

	if (conv == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		return (1);
	}
	else if (conv == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (conv == 'p')
		return (ft_printptr(va_arg(args, void *)));
	else if (conv == 'd' || conv == 'i')
		return (ft_printnbr(va_arg(args, long int)));
	else if (conv == 'u')
		return (ft_printuns(va_arg(args, unsigned int)));
	else if (conv == 'x' || conv == 'X')
	{
		longint = (unsigned long int)va_arg(args, unsigned int);
		return (ft_printhex(longint, conv));
	}
	else if (conv == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int			i;
	int			len;
	va_list		args;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] != '%')
			len += write(1, &format[i], 1);
		else
		{
			len += ft_print_conversion(format[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
