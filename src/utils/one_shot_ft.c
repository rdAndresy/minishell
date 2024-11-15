#include "minishell.h"

char	*ft_random_string(void)
{
	int		fd;
	char	*res;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = malloc(sizeof(char) * 9);
	if (!res)
		return (close(fd), NULL);
	if (read(fd, res, 8) < 0)
		return (close(fd), free(res), NULL);
	res[8] = '\0';
	return (close(fd), res);
}

static int	ft_nbsep(const char *s, char c)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (!*s)
		return (size);
	if (s[i] != c || ft_checkquote((char *)s, i))
	{
		i++;
		size++;
	}
	while (s[i])
	{
		if (s[i + 1] && s[i] == c && !ft_checkquote((char *)s, i)
			&& (s[i + 1] != c || ft_checkquote((char *)s, i + 1)))
			size++;
		i++;
	}
	return (size);
}

static char	*ft_strdup_substr(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && (s[i] != c || ft_checkquote(s, i)))
		i++;
	return (ft_substr(s, 0, (size_t)i));
}

char	**ft_split_withquotes(char const *s, char c)
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
		while (s[i] == c && !ft_checkquote((char *)s, i))
			i++;
		if (s[i])
			dst[j++] = ft_strdup_substr((char *)(s + i), c);
		while (s[i] && (s[i] != c || ft_checkquote((char *)s, i)))
			i++;
	}
	dst[j] = 0;
	return (dst);
}

// Get the current process id with authorized functions
int	ft_get_current_pid(void)
{
	int		fd;
	int		pid;
	char	*line;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	pid = ft_atoi(line);
	free(line);
	close(fd);
	return (pid);
}
