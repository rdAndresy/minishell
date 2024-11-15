#include "builtins.h"

int	ft_export_join(t_mini **env, char **key, char **value)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	res = NULL;
	if (!value || !(*value))
	{
		res = ft_strdup(*key);
		if (!res)
			return (EXIT_FAILURE);
	}
	else
	{
		tmp = ft_strjoin(*key, "=");
		if (!tmp)
			return (EXIT_FAILURE);
		res = ft_strjoin(tmp, *value);
		if (!res)
			return (free(tmp), EXIT_FAILURE);
	}
	ft_lstadd_back_env(&(*env)->env, ft_lstnew_env(res, 0));
	(ft_rank_env(&(*env)->env), ft_frees(4, tmp, res, *key, *value));
	if (!ft_lstlast_env((*env)->env))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_create_strs(char *cmd, char **key, char **value, int equal)
{
	if (!equal)
		return (EXIT_FAILURE);
	else if (equal == -1)
	{
		*key = ft_strdup(cmd);
		if (!(*key))
			return (EXIT_FAILURE);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(cmd, 0, equal);
		if (!(*key))
			return (EXIT_FAILURE);
		if (cmd[equal] == '+')
			*value = ft_substr(cmd, equal + 2, ft_strlen(cmd) - equal);
		else
			*value = ft_substr(cmd, equal + 1, ft_strlen(cmd) - equal);
		if (!(*value))
			return (free(*key), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_switch_equal(t_env **tmp, char *value, char equal, char *key)
{
	char	*tmp_char;

	if (equal && equal == '+')
	{
		tmp_char = ft_strjoin((*tmp)->value, value);
		if (!tmp_char)
			return (ft_frees(2, key, value), EXIT_FAILURE);
		(ft_frees(2, value, (*tmp)->value), (*tmp)->value = tmp_char);
	}
	else if (equal)
	{
		(free((*tmp)->value), (*tmp)->value = value);
		if (!(*tmp)->value)
			return (ft_frees(2, key, value), EXIT_FAILURE);
	}
	return (free(key), EXIT_SUCCESS);
}

int	ft_export_value(char equal, t_mini **env, char *value, char *key)
{
	t_env	*tmp;

	tmp = (*env)->env;
	while (tmp && ft_strncmp(tmp->key, key, PATH_MAX))
		tmp = tmp->next;
	if (tmp)
		return (ft_switch_equal(&tmp, value, equal, key));
	else
		return (ft_export_join(env, &key, &value));
}

int	my_export(char **cmd, t_mini **env, char *key, char *value)
{
	int		equal;
	int		i;

	i = 1;
	if (!cmd[i])
		return (ft_print_export((*env)->env), EXIT_SUCCESS);
	while (cmd && cmd[i])
	{
		key = NULL;
		value = NULL;
		equal = ft_check_arg(&cmd[i]);
		if (!ft_create_strs(cmd[i], &key, &value, equal))
		{
			if (equal != -1)
			{
				if (ft_export_value(cmd[i][equal], env, value, key))
					return (EXIT_FAILURE);
			}
			else if (ft_export_value(0, env, value, key))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
