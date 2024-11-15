#include "libft.h"

void	ft_frees(int count, ...)
{
	va_list		args;
	int			i;
	char		*str;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		str = va_arg(args, char *);
		free(str);
		i++;
	}
	va_end(args);
}
