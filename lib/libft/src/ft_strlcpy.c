#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = -1;
	srclen = ft_strlen(src);
	if (srclen + 1 < size)
		while (++i < srclen + 1)
			dst[i] = src[i];
	else if (size > 0)
	{
		while (++i < size - 1)
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (srclen);
}
