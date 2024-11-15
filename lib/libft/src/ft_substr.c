#include "libft.h"

char	*ft_substr(char const *s, int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s + start);
	if (i < len)
		len = i;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	j = start;
	while (s[j] && j < len + start)
	{
		dst[j - start] = s[j];
		j++;
	}
	dst[j - start] = 0;
	return (dst);
}
