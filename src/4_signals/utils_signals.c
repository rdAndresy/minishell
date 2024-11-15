#include "execution.h"

int	ft_check_shell_level(t_mini *env)
{
	t_env	*tmp;

	tmp = env->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
		{
			if (ft_atoi(tmp->value) > 2)
				return (EXIT_FAILURE);
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
