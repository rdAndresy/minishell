#include "libft.h"

int	ft_printstr(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_printnbr(long int nbr)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

int	ft_printuns(unsigned int nbr)
{
	char	c;
	int		len;

	len = 0;
	if (nbr >= 10)
		len = ft_printuns(nbr / 10);
	c = nbr % 10 + '0';
	return (len + write(1, &c, 1));
}

int	ft_printhex(unsigned long int nbr, int conv)
{
	char	*base_up;
	char	*base_down;
	int		len;

	len = 0;
	base_up = "0123456789ABCDEF";
	base_down = "0123456789abcdef";
	if (nbr == 0)
		return (write(1, &base_up[0], 1));
	if (nbr > 15)
		len = ft_printhex(nbr / 16, conv);
	if (conv == 'x')
		return (len + write(1, &base_down[nbr % 16], 1));
	else
		return (len + write(1, &base_up[nbr % 16], 1));
}

int	ft_printptr(void *ptr)
{
	int	len;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	else
	{
		len = write(1, "0x", 2);
		return (len + ft_printhex((unsigned long int)ptr, 'x'));
	}
}
