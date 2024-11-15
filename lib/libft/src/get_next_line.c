#include "libft.h"

char	*ft_rest(char *dst)
{
	char	*res;
	int		i;

	i = 0;
	while (dst[i] && dst[i] != '\n')
		i++;
	if (!dst[i])
	{
		free(dst);
		return (NULL);
	}
	res = ft_substr(dst, i + 1, ft_strlen(dst) - i);
	if (!res[0])
	{
		free(res);
		res = NULL;
	}
	free(dst);
	return (res);
}

char	*ft_get_line(char *dst)
{
	char	*line;
	int		i;

	if (!dst[0])
		return (NULL);
	i = 0;
	while (dst[i] && dst[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (dst[i] && dst[i] != '\n')
	{
		line[i] = dst[i];
		i++;
	}
	line[i++] = 0;
	return (line);
}

char	*ft_new_dst(char *dst, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(dst, buf);
	free(dst);
	return (tmp);
}

char	*ft_read_until(int fd, char *dst)
{
	char	*buf;
	int		rank;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rank = 1;
	while (rank > 0)
	{
		rank = read(fd, buf, BUFFER_SIZE);
		if (rank == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rank] = 0;
		dst = ft_new_dst(dst, buf);
		if (ft_strchr(buf, '\n'))
			rank = -1;
	}
	free(buf);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*dst;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!dst)
	{
		dst = (char *)malloc(sizeof(char));
		dst[0] = 0;
	}
	dst = ft_read_until(fd, dst);
	if (!dst)
		return (NULL);
	res = ft_get_line(dst);
	dst = ft_rest(dst);
	return (res);
}
