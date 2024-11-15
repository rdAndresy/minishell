#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
