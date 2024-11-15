#include "signals.h"

char	**ft_to_table(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**res;
	char	*old;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		old = ft_strjoin(tmp->key, "=");
		res[i] = ft_strjoin(old, tmp->value);
		(free(old), i++, tmp = tmp->next);
	}
	return (res[i] = NULL, res);
}

int	ft_rank_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		i;

	tmp1 = *env;
	while (tmp1)
	{
		i = 0;
		tmp2 = *env;
		while (tmp2)
		{
			if (ft_strncmp(tmp1->key, tmp2->key, PATH_MAX) > 0
				&& tmp1 != tmp2)
				i++;
			tmp2 = tmp2->next;
		}
		tmp1->index = i;
		tmp1 = tmp1->next;
	}
	return (EXIT_SUCCESS);
}

t_env	*setup_bash_env(char **input)
{
	int		i;
	t_env	*env;
	char	cwd[PATH_MAX];
	char	*tmp;

	i = 0;
	env = NULL;
	if (!input || !input[0]
		|| !ft_strncmp(input[0], "VALGRIND_LIB", 12))
	{
		env = ft_lstnew_env("SHLVL=0", i++);
		if (getcwd(cwd, PATH_MAX))
		{
			tmp = ft_strjoin("PWD=", cwd);
			(ft_lstadd_back_env(&env, ft_lstnew_env(tmp, i++)), free(tmp));
		}
		ft_lstadd_back_env(&env, ft_lstnew_env("_=/usr/bin/env", i));
	}
	else
		while (input[i])
			ft_lstadd_back_env(&env, ft_lstnew_env(input[i++], 0));
	if (!ft_lstlast_env(env) || ft_rank_env(&env))
		return (ft_perror("environment creation error"), NULL);
	return (env);
}

t_mini	*setup_env(char **input)
{
	t_mini	*res;

	res = malloc(sizeof(*res));
	if (!res)
		return (ft_perror("environment creation error"), NULL);
	res->return_val = 0;
	res->env = setup_bash_env(input);
	if (!res->env)
		return (free(res), ft_perror("environment creation error"), NULL);
	res->table_env = ft_to_table(res->env);
	if (!res->table_env)
		return (ft_lstclear_env(&res),
			ft_perror("environment creation error"), NULL);
	res->curr_cmds = NULL;
	res->fd_stdin = dup(STDIN_FILENO);
	if (res->fd_stdin == -1)
		return (ft_lstclear_env(&res), ft_perror("stdin dup error"), NULL);
	res->fd_stdout = dup(STDOUT_FILENO);
	if (res->fd_stdout == -1)
		return (ft_lstclear_env(&res), ft_perror("stdout dup error"), NULL);
	res->b_exit = 0;
	res->b_interact = 0;
	return (res);
}
