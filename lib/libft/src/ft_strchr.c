#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	c = (char)c;
	while (*str != c && *str)
		str++;
	if (*str != c)
		return (NULL);
	return (str);
}
