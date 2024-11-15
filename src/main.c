#include "minishell.h"

int	g_sig;

int	main(int ac, char *av[], char *envp[])
{
	t_mini	*env;
	int		end;

	env = setup_env(envp);
	if (!isatty(STDIN_FILENO))
		env->return_val = ft_non_interact_pipe(env);
	else if (av[1] && !ft_strncmp(av[1], "-c", ft_max(2, ft_strlen(av[1]), 2)))
		env->return_val = ft_non_interact_args(env, av[2]);
	else if (ac != 1 || av[1])
	{
		ft_perror("Program does not accept any argument");
		env->return_val = EXIT_FAILURE;
	}
	else
	{
		env->return_val = ft_interact(env);
		if (env->b_exit != 2)
			printf("exit\n");
	}
	end = env->return_val;
	rl_clear_history();
	ft_lstclear_env(&env);
	return (end);
}
