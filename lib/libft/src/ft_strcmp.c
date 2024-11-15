#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	if ((int)i == ft_strlen(s1) && (int)i == ft_strlen(s2))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
