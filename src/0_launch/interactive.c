#include "minishell.h"

void	ft_launch(t_mini *env, int *times, char *input)
{
	if (g_sig != 0)
	{
		if (*times == 1)
			printf("\n");
		if (dup2(env->fd_stdin, STDIN_FILENO) != -1)
			env->return_val = ft_return(g_sig);
		else
		{
			ft_perror("dup2 failed");
			env->return_val = EXIT_FAILURE;
		}
	}
	if (input)
	{
		*times = 0;
		if (input[0])
			(add_history(input), env->return_val = lexer(input, env, 0, 0));
	}
}

char	*ft_display_prompt(t_mini *env, int *error)
{
	int		fd;
	char	*input;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		return (ft_perror("fail to open stdin"), *error = 1, NULL);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), ft_perror("fail to open stdin"), *error = 1, NULL);
	(close(fd), fd = open("/dev/tty", O_WRONLY));
	if (fd == -1)
		return (ft_perror("opening of stdin failed"), *error = 1, NULL);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), ft_perror("fail to open stdin"), *error = 1, NULL);
	(close(fd), ft_handle_signals_main());
	if (env->return_val == 0)
		input = readline(BLUE_MINI);
	else
		input = readline(RED_MINI);
	if (dup2(env->fd_stdin, 0) == -1 || dup2(env->fd_stdout, 1) == -1)
	{
		if (input)
			free(input);
		return (ft_perror("fail to open stdin"), *error = 1, NULL);
	}
	return (input);
}

int	ft_interact(t_mini *env)
{
	char	*input;
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (env->b_exit == 0 && ++i)
	{
		input = ft_display_prompt(env, &error);
		if (!input && g_sig == 0)
		{
			if (error == 1)
				env->return_val = 2;
			break ;
		}
		ft_launch(env, &i, input);
	}
	return (env->return_val);
}
