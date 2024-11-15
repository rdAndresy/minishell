#include "libft.h"

int	ft_printstr_fd(char *str, int fd)
{
	if (!str)
		return (write(fd, "(null)", 6));
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	ft_printnbr_fd(long int nbr, int fd)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr);
	len = ft_strlen(str);
	ft_putstr_fd(str, fd);
	free(str);
	return (len);
}

int	ft_printuns_fd(unsigned int nbr, int fd)
{
	char	c;
	int		len;

	len = 0;
	if (nbr >= 10)
		len = ft_printuns_fd(nbr / 10, fd);
	c = nbr % 10 + '0';
	return (len + write(fd, &c, 1));
}

int	ft_printhex_fd(unsigned long int nbr, int conv, int fd)
{
	char	*base_up;
	char	*base_down;
	int		len;

	len = 0;
	base_up = "0123456789ABCDEF";
	base_down = "0123456789abcdef";
	if (nbr == 0)
		return (write(fd, &base_up[0], 1));
	if (nbr > 15)
		len = ft_printhex_fd(nbr / 16, conv, fd);
	if (conv == 'x')
		return (len + write(fd, &base_down[nbr % 16], 1));
	else
		return (len + write(fd, &base_up[nbr % 16], 1));
}

int	ft_printptr_fd(void *ptr, int fd)
{
	int	len;

	if (ptr == 0)
		return (write(fd, "(nil)", 5));
	else
	{
		len = write(fd, "0x", 2);
		return (len + ft_printhex_fd((unsigned long int)ptr, 'x', fd));
	}
}
