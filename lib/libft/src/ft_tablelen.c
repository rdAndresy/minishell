#include "libft.h"

int	ft_tablelen(char *table[])
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}
