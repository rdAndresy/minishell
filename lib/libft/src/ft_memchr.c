#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (((unsigned char *)s)[i] != (unsigned char)c && i < n)
		i++;
	if (((unsigned char *)s)[i] != (unsigned char)c || i >= n)
		return (NULL);
	return ((void *)s + i);
}
