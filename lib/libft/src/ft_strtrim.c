#include "libft.h"

static int	ft_isset(char c, const char *const_set)
{
	char	*set;

	set = (char *)const_set;
	while (*set != c && *set)
		set++;
	if (*set != c)
		return (0);
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		i;
	int		start;
	int		end;

	start = 0;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	end = 0;
	while (s1[end])
		end++;
	while (end > start && ft_isset(s1[end - 1], set))
		end--;
	dst = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (start < end)
		dst[i++] = s1[start++];
	dst[i] = 0;
	return (dst);
}
