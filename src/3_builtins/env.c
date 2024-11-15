#include "builtins.h"

int	my_env(char **cmd, t_mini *env)
{
	t_env	*tmp;

	tmp = env->env;
	if (cmd || !cmd || env || !env)
	{
		while (tmp)
		{
			if (tmp->value)
				ft_fprintf(STDOUT_FILENO, "%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);
}
