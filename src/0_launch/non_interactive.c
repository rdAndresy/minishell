#include "minishell.h"

int	ft_non_interact_args(t_mini *env, char *av)
{
	char	*res;

	res = ft_strdup(av);
	if (!res)
		return (ft_perror("malloc failed"), EXIT_FAILURE);
	env->return_val = lexer(res, env, 0, 0);
	return (env->return_val);
}

int	ft_non_interact_pipe(t_mini *env)
{
	char	buffer[PATH_MAX];
	char	*res;
	int		len;

	env->b_interact = 1;
	res = ft_strdup("");
	if (!res)
		return (ft_perror("malloc failed"), EXIT_FAILURE);
	len = 1;
	while (len != 0)
	{
		len = read(STDIN_FILENO, buffer, PATH_MAX - 1);
		if (len == -1)
			return (ft_perror("read error"), EXIT_FAILURE);
		buffer[len] = '\0';
		buffer[len - 1] = '\0';
		res = ft_strdup(buffer);
		if (!res)
			return (ft_perror("malloc failed"), EXIT_FAILURE);
		env->return_val = lexer(ft_strdup(res), env, 0, 0);
	}
	return (env->return_val);
}
