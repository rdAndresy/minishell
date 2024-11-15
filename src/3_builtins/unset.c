#include "builtins.h"

void	ft_go_unset(char *cmd, t_mini **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = (*env)->env;
	if (!ft_strncmp(tmp->key, cmd, PATH_MAX))
	{
		(*env)->env = tmp->next;
		ft_frees(3, tmp->value, tmp->key, tmp);
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, cmd, PATH_MAX))
		{
			prev->next = tmp->next;
			ft_frees(3, tmp->value, tmp->key, tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	my_unset(char **cmd, t_mini **env)
{
	int		i;

	i = 1;
	if (!cmd[i])
		return (EXIT_SUCCESS);
	while (cmd[i])
		ft_go_unset(cmd[i++], env);
	if (ft_rank_env(&(*env)->env))
		return (ft_perror("unset: malloc failed"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
