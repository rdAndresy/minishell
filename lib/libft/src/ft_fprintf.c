#include "libft.h"

void	ft_strjoin_conv(char **res, char conv, va_list *args)
{
	char	*tmp1;
	char	*tmp2;
	char	tmp3[2];

	if (conv == 's')
		tmp1 = ft_strdup(va_arg(*args, char *));
	else if (conv == 'c')
	{
		tmp3[0] = va_arg(*args, int);
		tmp3[1] = '\0';
		tmp1 = ft_strdup(tmp3);
	}
	else
		tmp1 = ft_itoa(va_arg(*args, int));
	tmp2 = ft_strjoin(*res, tmp1);
	free(tmp1);
	free(*res);
	*res = tmp2;
}

void	ft_update_res(char **res, const char *format, int i, int j)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(format, i, j);
	tmp2 = ft_strjoin(*res, tmp1);
	free(tmp1);
	free(*res);
	*res = tmp2;
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int			i;
	int			j;
	char		*res;
	va_list		args;

	if (fd < 1)
		return (write(2, "Wrong fd output selected\n", 25), 0);
	(va_start(args, format), i = 0, res = ft_strdup(""));
	if (!res)
		return (0);
	while (format[i])
	{
		j = 0;
		while (format[i + j] && format[i + j] != '%')
			j++;
		(ft_update_res(&res, format, i, j), i += j);
		if (!res)
			return (0);
		if (format[i] && format[i] == '%')
			(ft_strjoin_conv(&res, format[i + 1], &args), i += 2);
		if (!res)
			return (EXIT_FAILURE);
	}
	return (write(fd, res, ft_strlen(res)), free(res),
		va_end(args), EXIT_SUCCESS);
}
