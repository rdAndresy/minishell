#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1)
		dst = ft_strdup(s2);
	else if (!s2)
		dst = ft_strdup(s1);
	else
		dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	if (!s1 || !s2)
		return (dst);
	i = 0;
	j = 0;
	while (s1[i])
		dst[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dst[j++] = s2[i++];
	dst[j] = 0;
	return (dst);
}
