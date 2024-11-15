#include "lexer.h"

void	ft_link_redir(t_token **cmd)
{
	t_token	*tmp;
	t_redir	*curr;
	t_redir	*prev;

	tmp = *cmd;
	while (tmp)
	{
		if (!tmp->redir)
			return ;
		curr = tmp->redir->next;
		prev = tmp->redir;
		while (curr)
		{
			curr->previous = prev;
			prev = curr;
			curr = curr->next;
		}
		tmp = tmp->next;
	}
}

int	ft_err_redir(int *fd, int type, char *file, int res)
{
	struct stat	buf;

	res = stat(file, &buf);
	access(file, R_OK | W_OK);
	if (*fd == -1 && type != HERE_DOC && errno == EACCES)
		return (ft_perror("%s: Permission denied", file), EXIT_FAILURE);
	if (*fd == -1 && ft_strlen(file) - 1 < 0)
		return (ft_perror("%s: Ambiguous redirect", file), EXIT_FAILURE);
	if (*fd == -1 && file[ft_strlen(file) - 1] == '/' && !ft_strchr(file, ' '))
		return (ft_perror("%s: Not a directory", file), EXIT_NOT_A_DIR);
	if (*fd == -1 && res != -1 && S_ISDIR(buf.st_mode)
		&& (type == OUTFILE || type == APPEND))
		return (ft_perror("%s: Is a directory", file), EXIT_DIR_NOT_FOUND);
	if (*fd == -1 && type == HERE_DOC)
		return (ft_perror("here_doc: Open failed"), EXIT_FAILURE);
	if (*fd == -1 && type != HERE_DOC)
		return (ft_perror("%s: No such file or directory", file), EXIT_FAILURE);
	if (*fd == -2)
		*fd = -1;
	return (EXIT_SUCCESS);
}

int	ft_err_cmd(t_token *tmp)
{
	struct stat	buf;
	int			res;

	if (!ft_strncmp(tmp->cmd, ERROR_NOT_A_DIR, 26))
		return (ft_perror("%s: Not a directory", tmp->args[0]),
			EXIT_NOT_A_DIR);
	if (tmp->is_builtin)
		return (EXIT_SUCCESS);
	res = stat(tmp->args[0], &buf);
	if (res != -1 && (S_ISDIR(buf.st_mode) || errno == EACCES))
		return (ft_directory_error(&tmp, buf, res));
	if (!ft_strncmp(tmp->cmd, ERROR_DIR_NOT_FOUND, ft_strlen(tmp->cmd))
		|| !ft_strncmp(tmp->cmd, ERROR_NO_ENV, ft_strlen(tmp->cmd))
		|| !ft_strncmp(tmp->cmd, ERROR_NO_SUCH_FOD, ft_strlen(tmp->cmd)))
		return (ft_perror("%s: No such file or directory", tmp->args[0]),
			EXIT_NO_SUCH_FOD);
	if ((!ft_strncmp(tmp->cmd, ERROR_CMD_NOT_FOUND, ft_strlen(tmp->cmd)))
		|| (!ft_strncmp(tmp->cmd, ERROR_DIR_NOT_FOUND, ft_strlen(tmp->cmd))))
		return (ft_perror("%s: Command not found", tmp->args[0]),
			EXIT_CMD_NOT_FOUND);
	return (EXIT_SUCCESS);
}

int	ft_no_cmd(t_token *cmds)
{
	char	**args;

	args = (char **)malloc(sizeof(char *) * 2);
	if (!args)
		return (EXIT_FAILURE);
	args[0] = cmds->cmd;
	if (ft_strncmp(args[0], ERROR_EMPTY_CMD, ft_strlen(ERROR_EMPTY_CMD)) == 0)
	{
		ft_perror(": Command not found");
		cmds->cmd = ft_strdup(ERROR_EMPTY_CMD);
	}
	else
		cmds->cmd = ft_strdup(ERROR_NO_CMD);
	args[1] = NULL;
	if (!args[0])
	{
		free(args);
		return (EXIT_FAILURE);
	}
	cmds->args = args;
	return (EXIT_SUCCESS);
}

int	checker(t_token *cmds, t_mini *env)
{
	t_token	*tmp;
	t_redir	*redir;

	tmp = ft_lstlast_token(cmds);
	while (tmp && !g_sig)
	{
		if (tmp->redir)
		{
			redir = tmp->redir;
			while (redir)
			{
				ft_err_redir(&redir->fd, redir->type, redir->file, 0);
				redir = redir->next;
			}
		}
		if (!tmp->args)
			if (ft_no_cmd(tmp))
				return (ft_token_error("parser: malloc failed", NULL, cmds));
		if (!tmp->err_redir)
			if (ft_err_cmd(tmp) == EXIT_FAILURE)
				return (ft_token_error("parser: malloc failed", NULL, cmds));
		tmp = tmp->previous;
	}
	ft_link_redir(&cmds);
	return (execution(cmds, env));
}
