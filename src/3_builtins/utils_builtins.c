#include "builtins.h"

void	ft_print_export(t_env *env)
{
	t_env	*tmp;
	int		i;
	int		max;

	max = ft_lstsize_env(env);
	i = 0;
	while (i < max)
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->index == i)
			{
				printf("export %s", tmp->key);
				if (tmp->value && tmp->value[0] != '\0')
					printf("=\"%s\"\n", tmp->value);
				else if (tmp->value && tmp->value[0] == '\0')
					printf("=\"\"\n");
				else
					printf("\n");
			}
			tmp = tmp->next;
		}
		i++;
	}
}

// checks if the first character of the future variable name is only letters or
// underscores, and if the following characters are only letters, numbers, 
// underscores or a single += sign
int	ft_check_arg(char **str)
{
	int		i;

	i = 0;
	if (!(((*str)[i] >= 'A' && (*str)[i] <= 'Z')
		|| ((*str)[i] >= 'a' && (*str)[i] <= 'z')
		|| ((*str)[i] == '_')))
		return (ft_perror("export: `%s': not a valid identifier",
				(*str)), EXIT_SUCCESS);
	i++;
	while ((*str)[i] && (*str)[i] != '=')
	{
		if (!ft_isalnum((*str)[i]) && (*str)[i] != '_'
			&& ((*str)[i] != '+' || (*str)[i + 1] != '='))
			return (ft_perror("export: `%s': not a valid identifier",
					(*str)), EXIT_SUCCESS);
		i++;
	}
	if ((*str)[i] && (*str)[i] == '=' && (*str)[i - 1] == '+')
		return (i - 1);
	else if ((*str)[i] && (*str)[i] == '=')
		return (i);
	else
		return (-1);
}

int	ft_update_pwd(t_env **env)
{
	t_env	*tmp;
	int		index;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE);
	tmp = (*env);
	while (tmp && ft_strncmp(tmp->key, "PWD",
			ft_max(2, ft_strlen(tmp->key), 3)))
	{
		index = tmp->index;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_lstadd_back_env(env, ft_lstnew_env("PWD=x", ++index));
		if (ft_strncmp(ft_lstlast_env(*env)->key, "PWD", 3))
			return (EXIT_FAILURE);
		tmp = ft_lstlast_env((*env));
	}
	free(tmp->value);
	tmp->value = ft_strdup(cwd);
	if (!tmp->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
