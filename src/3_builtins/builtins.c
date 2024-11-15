#include "builtins.h"

int	ft_select(char **cmds, t_mini *env, int in_exec)
{
	if (in_exec != IN_CHILD_EXEC)
	{
		if (!ft_strncmp(cmds[0], "cd", ft_max(2, ft_strlen(cmds[0]), 3)))
			return (my_cd(cmds, &env));
		else if (!ft_strncmp(cmds[0], "exit", ft_max(2, ft_strlen(cmds[0]), 5)))
			return (my_exit(cmds, &env, OUT_CHILD_EXEC));
		else if (!ft_strncmp(cmds[0], "export",
				ft_max(2, ft_strlen(cmds[0]), 7)))
			return (my_export(cmds, &env, NULL, NULL));
		else if (!ft_strncmp(cmds[0], "unset",
				ft_max(2, ft_strlen(cmds[0]), 6)))
			return (my_unset(cmds, &env));
	}
	if (!ft_strncmp(cmds[0], "echo", ft_max(2, ft_strlen(cmds[0]), 5)))
		return (my_echo(cmds));
	else if (!ft_strncmp(cmds[0], "env", ft_max(2, ft_strlen(cmds[0]), 4)))
		return (my_env(cmds, env));
	else if (!ft_strncmp(cmds[0], "exit", ft_max(2, ft_strlen(cmds[0]), 5)))
		return (my_exit(cmds, &env, IN_CHILD_EXEC));
	else if (!ft_strncmp(cmds[0], "pwd", ft_max(2, ft_strlen(cmds[0]), 4)))
		return (my_pwd(cmds, env));
	return (EXIT_SUCCESS);
}

int	ft_builtin_exec(t_exec *exec, int in_exec)
{
	int	val_return;

	ft_handle_signals_builtins();
	val_return = ft_select(exec->curr->args, exec->env, in_exec);
	if (in_exec == IN_CHILD_EXEC)
		ft_exit_child(exec, val_return);
	return (val_return);
}

int	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_max(2, ft_strlen(cmd), 3)))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp(cmd, "exit", ft_max(2, ft_strlen(cmd), 5)))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp(cmd, "export", ft_max(2, ft_strlen(cmd), 7)))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp(cmd, "unset", ft_max(2, ft_strlen(cmd), 6)))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
