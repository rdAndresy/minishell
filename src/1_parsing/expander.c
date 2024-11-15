#include "lexer.h"

// Create a new command string by removing the expanded part
int	ft_create_new_cmd(char **cmd, int i, int j, char *expand)
{
	char	*cmd_left;
	char	*cmd_right;
	char	*new_cmd;

	cmd_left = ft_substr(*cmd, 0, i);
	if (!cmd_left)
		return (EXIT_FAILURE);
	if (expand)
		cmd_right = ft_substr(*cmd, i + j, ft_strlen(*cmd) - i - j);
	else if (!expand && j == -1)
		cmd_right = ft_substr(*cmd, i - j, ft_strlen(*cmd) - i + j);
	else
		cmd_right = ft_substr(*cmd, i + j, ft_strlen(*cmd) - i - j);
	if (!cmd_right)
		return (free(cmd_left), EXIT_FAILURE);
	if (expand)
		new_cmd = ft_strjoin(cmd_left, expand);
	else
		new_cmd = ft_strdup(cmd_left);
	if (!new_cmd)
		return (ft_frees(2, cmd_right, cmd_left), EXIT_FAILURE);
	(ft_frees(2, cmd_left, *cmd), *cmd = ft_strjoin(new_cmd, cmd_right));
	if (!*cmd)
		return (ft_frees(2, new_cmd, cmd_right), EXIT_FAILURE);
	return (ft_frees(2, new_cmd, cmd_right), EXIT_SUCCESS);
}

// Get the global variable from the command line
int	ft_get_expand(char **cmd, t_mini *env, int mode, int *i)
{
	int		j;
	char	*var;
	char	*expand;

	j = 1;
	while ((*cmd)[*i + j] && (*cmd)[*i + j] != '$'
		&& (*cmd)[*i + j] != ' ' && (*cmd)[*i + j] != '\"'
		&& (*cmd)[*i + j] != '\'' && (*cmd)[*i + j] != '/'
		&& ((ft_checkquote(*cmd, *i + j) != 1 && mode == CMD)
			|| mode == HERE_DOC))
		j++;
	var = ft_substr(*cmd, *i + 1, j - 1);
	if (!var)
		return (free(*cmd), *cmd = NULL, EXIT_FAILURE);
	expand = ft_getenv(env, var);
	if (ft_create_new_cmd(cmd, *i, j, expand))
		return (ft_frees(3, var, expand, *cmd), *cmd = NULL, EXIT_FAILURE);
	if (expand)
		*i += ft_strlen(expand) - (ft_strlen(var) - 1);
	else
		*i -= ft_strlen(var) + 1;
	if (*i < 0)
		*i = 0;
	ft_frees(2, var, expand);
	return (EXIT_SUCCESS);
}

// Expand special variables ($$ and $?)
// !! get_last_return_value() is always 0 for now !!
void	ft_expand_special(char **cmd, int *i, int return_val)
{
	char	*expand;

	expand = NULL;
	if ((*cmd)[*i + 1] == '$')
		expand = ft_itoa(ft_get_current_pid());
	else if ((*cmd)[*i + 1] == '?')
		expand = ft_itoa(return_val);
	if (!expand)
	{
		free(*cmd);
		*cmd = NULL;
		return ;
	}
	if (ft_create_new_cmd(cmd, *i, 2, expand))
	{
		ft_frees(2, expand, *cmd);
		*cmd = NULL;
		return ;
	}
	*i += ft_strlen(expand) - 1;
	free (expand);
}

// Iterates on the command and check if expand is needed, then execute
// relevant expand: special ($$ or $?), global variable or nothing
int	ft_expand(char **cmd, t_mini *env, int mode, int i)
{
	while (*cmd && (*cmd)[i] && (*cmd)[i + 1])
	{
		if ((*cmd)[i] == '$' && (*cmd)[i + 1] != ' ' && (*cmd)[i + 1] != '\''
			&& (*cmd)[i + 1] != '\"' && (mode == HERE_DOC || (mode == CMD
				&& ft_checkquote(*cmd, i) != 1)))
		{
			if ((*cmd)[i + 1] == '$' || (*cmd)[i + 1] == '?')
				ft_expand_special(cmd, &i, env->return_val);
			else
				ft_get_expand(cmd, env, mode, &i);
		}
		else if ((*cmd)[i] == '$' && (*cmd)[i + 1] && ((*cmd)[i + 1] == ' '
			|| (*cmd)[i + 1] == '\t' || (ft_checkquote(*cmd, i)
			&& ((*cmd)[i + 1] == '\'' || (*cmd)[i + 1] == '\"'))))
			i++;
		else if ((*cmd)[i] == '$' && mode == CMD && ft_checkquote(*cmd, i) != 1)
			ft_create_new_cmd(cmd, i, -1, NULL);
		if ((*cmd)[i])
			i++;
	}
	if (!(*cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Expand the relevant global variable (including $? & $$) by iterating on both
// commands & redirections, return error only with malloc errors
int	expander(t_token *cmds, t_mini *env)
{
	t_token	*tmp;
	t_redir	*tmp_redir;

	tmp = cmds;
	while (tmp)
	{
		if (ft_expand(&tmp->cmd, env, CMD, 0))
			return (ft_token_error("expander: malloc failed", NULL, cmds));
		if (tmp->redir)
		{
			tmp_redir = tmp->redir;
			while (tmp_redir)
			{
				if (tmp_redir->type != HERE_DOC
					&& ft_expand(&tmp_redir->file, env, CMD, 0))
					break ;
				tmp_redir = tmp_redir->next;
			}
			if (tmp_redir)
				return (ft_token_error("expander: malloc failed",
						NULL, cmds));
		}
		tmp = tmp->next;
	}
	return (parser(cmds, env));
}
