#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (size != 0 && count > (sizeof(char) * 2147483424) / size)
		return (0);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	while (i < count * size)
		*(unsigned char *)(ptr + i++) = 0;
	return (ptr);
}
