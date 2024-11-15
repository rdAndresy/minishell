#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dst;

	i = 0;
	while (s[i])
		i++;
	dst = (char *)malloc(i + 1);
	if (!dst)
		return (0);
	i = 0;
	while (s[i])
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	dst[i] = 0;
	return (dst);
}
