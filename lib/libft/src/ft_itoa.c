#include "libft.h"

static char	*ft_rev_int_tab(char *tab, int size)
{
	int		i;
	char	temp;

	i = 0;
	while (i < size / 2)
	{
		temp = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = temp;
		i++;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	int			i;
	int			sign;
	long int	nbr;
	char		dst[33];

	nbr = (long int)n;
	if (nbr == 0)
		return (ft_strdup("0"));
	sign = 1;
	if (nbr < 0)
	{
		sign *= -1;
		nbr *= -1;
	}
	i = 0;
	while (nbr != 0)
	{
		dst[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign == -1)
		dst[i++] = '-';
	dst[i] = 0;
	return (ft_strdup(ft_rev_int_tab(dst, i)));
}
