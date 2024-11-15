#include "libft.h"

static int	ft_nbsep(const char *s, char c)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (!*s)
		return (size);
	if (s[i] != c)
	{
		i++;
		size++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			size++;
		i++;
	}
	return (size);
}

static char	*ft_strdup_substr(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (ft_substr(s, 0, (size_t)i));
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**dst;

	if (!s)
		return (NULL);
	dst = malloc(sizeof(char **) * (ft_nbsep(s, c) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			dst[j++] = ft_strdup_substr((char *)(s + i), c);
		while (s[i] != c && s[i])
			i++;
	}
	dst[j] = 0;
	return (dst);
}
