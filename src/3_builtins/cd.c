#include "builtins.h"

static int	ft_update_oldpwd(t_env **env)
{
	t_env	*tmp;
	int		index;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE);
	tmp = (*env);
	while (tmp && ft_strncmp(tmp->key, "OLDPWD",
			ft_max(2, ft_strlen(tmp->key), 6)))
	{
		index = tmp->index;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_lstadd_back_env(env, ft_lstnew_env("OLDPWD=x", ++index));
		if (ft_strncmp(ft_lstlast_env(*env)->key, "OLDPWD", 6))
			return (EXIT_FAILURE);
		tmp = ft_lstlast_env((*env));
	}
	free(tmp->value);
	tmp->value = ft_strdup(cwd);
	if (!tmp->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_to_path(char *option, t_env **env)
{
	t_env	*tmp;
	char	*oldpwd;
	int		val_return;

	tmp = (*env);
	while (tmp && ft_strncmp(tmp->key, option,
			ft_max(2, ft_strlen(option), ft_strlen(tmp->key))))
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (ft_fprintf(2, "cd: %s not set\n", option), -2);
	else if (!ft_strncmp(option, "HOME", 4))
		return (chdir(tmp->value));
	else if (!ft_strncmp(option, "OLDPWD", 6))
	{
		oldpwd = ft_strdup(tmp->value);
		if (!oldpwd)
			return (-1);
		ft_update_oldpwd(env);
		val_return = chdir(oldpwd);
		free(oldpwd);
		return (val_return);
	}
	return (-1);
}

int	ft_check_errors(int ret, char **cmd, t_mini *env)
{
	char	cwd[PATH_MAX];
	char	*tmp;

	tmp = NULL;
	if (ret == -1 && (!cmd[1] || !ft_strncmp(cmd[1], "-", ft_strlen(cmd[1]))))
	{
		if (!cmd[1])
			tmp = ft_strdup("$HOME");
		else
			tmp = ft_strdup("$OLDPWD");
		ft_expand(&tmp, env, CMD, 0);
		if (!tmp)
			return (ft_perror("malloc failed"), EXIT_MALLOC);
		(ft_perror("%s: %s: %s", cmd[0], tmp, strerror(errno)), free(tmp));
		return (EXIT_FAILURE);
	}
	else if (ret == -1)
		return (ft_perror("%s: %s: %s", cmd[0], cmd[1],
				strerror(errno)), EXIT_FAILURE);
	else if (!getcwd(cwd, PATH_MAX) && cmd[1])
		return (ft_perror("%s: %s: No such file or directory",
				cmd[0], cmd[1]), EXIT_FAILURE);
	else if (ret == -2)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_go_home(t_mini **env)
{
	if (ft_update_oldpwd(&(*env)->env))
		ft_fprintf(STDERR_FILENO,
			"pwd: error retrieving current directory: " \
			"getcwd: cannot access parent directories: %s\n",
			strerror(errno));
	return (ft_to_path("HOME", &(*env)->env));
}

int	my_cd(char **cmd, t_mini **env)
{
	int		ret;

	if (g_sig)
		return (ft_return(g_sig));
	if (!cmd[1])
		ret = ft_go_home(env);
	else
	{
		if (cmd[2])
			return (ft_perror("%s: too many arguments", cmd[0]),
				EXIT_FAILURE);
		if (!ft_strncmp(cmd[1], "-", ft_strlen(cmd[1])))
		{
			ret = ft_to_path("OLDPWD", &(*env)->env);
			if (ret != -1 && ret != -2)
				my_pwd(NULL, (*env));
		}
		else
		{
			if (!access(cmd[1], X_OK))
				ft_update_oldpwd(&(*env)->env);
			ret = chdir(cmd[1]);
		}
	}
	return (ft_update_pwd(&(*env)->env), ft_check_errors(ret, cmd, (*env)));
}
