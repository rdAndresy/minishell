#include "lexer.h"

// Checks PATH for the command
char	*ft_check_paths(char **paths, char *cmd)
{
	int		i;
	char	*res;
	char	*tmp;

	if (!cmd[0])
		return (free(cmd), ft_strdup(ERROR_CMD_NOT_FOUND));
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (NULL);
	(free(cmd), i = 0);
	while (paths[i])
	{
		res = ft_strjoin(paths[i], tmp);
		if (!res)
			return (free(tmp), NULL);
		if (access(res, F_OK) == 0)
		{
			free(tmp);
			return (res);
		}
		free(res);
		i++;
	}
	return (free(tmp), ft_strdup(ERROR_CMD_NOT_FOUND));
}

// If the command is not a path towards a file, checks PATH for the command
char	*ft_find_cmd(char *cmd, t_mini *env)
{
	char	**paths;
	char	*res;
	t_env	*tmp;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		if (cmd[ft_strlen(cmd) - 1] == '/' && !ft_strchr(cmd, ' '))
			return (free(cmd), ft_strdup(ERROR_NOT_A_DIR));
		else
			return (free(cmd), ft_strdup(ERROR_NO_SUCH_FOD));
	}
	tmp = env->env;
	while (tmp && ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)))
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (free(cmd), ft_strdup(ERROR_NO_ENV));
	paths = ft_split(tmp->value, ':');
	if (!paths)
		return (free(cmd), NULL);
	res = ft_check_paths(paths, cmd);
	ft_free_table(paths);
	return (res);
}

// Parse the command and find the path
// The use of raw_paths prevents no-environment errors
int	ft_parse_cmd(t_token *cmd_struct, t_mini *env)
{
	if (!cmd_struct->cmd)
		return (EXIT_FAILURE);
	cmd_struct->args = ft_split_withquotes(cmd_struct->cmd, ' ');
	if (!cmd_struct->args)
		return (EXIT_FAILURE);
	free (cmd_struct->cmd);
	cmd_struct->cmd = ft_strdup(cmd_struct->args[0]);
	if (!cmd_struct->cmd)
		return (ft_free_table(cmd_struct->args), EXIT_FAILURE);
	if (ft_remove_token_quotes(cmd_struct))
		return (ft_free_table(cmd_struct->args), EXIT_FAILURE);
	if (!ft_strcmp(cmd_struct->cmd, "echo")
		|| !ft_strcmp(cmd_struct->cmd, "cd")
		|| !ft_strcmp(cmd_struct->cmd, "pwd")
		|| !ft_strcmp(cmd_struct->cmd, "env")
		|| !ft_strcmp(cmd_struct->cmd, "export")
		|| !ft_strcmp(cmd_struct->cmd, "unset")
		|| !ft_strcmp(cmd_struct->cmd, "exit"))
		cmd_struct->is_builtin = 1;
	else
		cmd_struct->cmd = ft_find_cmd(cmd_struct->cmd, env);
	if (!cmd_struct->cmd)
		return (ft_free_table(cmd_struct->args), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Parse the list of commands from the expander
int	parser(t_token *cmds, t_mini *env)
{
	t_token	*tmp;
	t_redir	*tmp_redir;
	int		i;

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		if (ft_is_spaces(tmp->cmd) && ft_parse_cmd(tmp, env))
			return (ft_token_error("parser: malloc failed", NULL, cmds));
		if (tmp->redir)
		{
			tmp_redir = tmp->redir;
			while (tmp_redir && !ft_rm_quotes(&tmp_redir->file)
				&& !ft_parse_redir(cmds, tmp, tmp_redir, env) && g_sig == 0)
				tmp_redir = tmp_redir->next;
			if (tmp_redir && g_sig == 0)
				return (ft_token_error("parser: malloc failed", NULL, cmds));
			if (g_sig != 0)
				return (ft_lstclear_token(&cmds), ft_return(g_sig));
		}
		tmp->index = i++;
		tmp = tmp->next;
	}
	return (checker(cmds, env));
}
