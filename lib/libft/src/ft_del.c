#include "libft.h"

void	ft_del(char *val)
{
	if (val)
		free(val);
}
