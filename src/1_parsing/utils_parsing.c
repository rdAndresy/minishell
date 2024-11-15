#include "lexer.h"

int	ft_directory_error(t_token **tmp, struct stat buf, int res)
{
	if (res != -1 && S_ISDIR(buf.st_mode))
	{
		(free((*tmp)->cmd), (*tmp)->cmd = ft_strdup(ERROR_DIR_NOT_FOUND));
		if (!(*tmp)->cmd)
			return (EXIT_FAILURE);
		return (ft_perror("%s: Is a directory", (*tmp)->args[0]),
			EXIT_DIR_NOT_FOUND);
	}
	else
	{
		(free((*tmp)->cmd), (*tmp)->cmd = ft_strdup(ERROR_DIR_NOT_FOUND));
		if (!(*tmp)->cmd)
			return (EXIT_FAILURE);
		return (ft_perror("%s: Permission denied", (*tmp)->args[0]),
			EXIT_DIR_NOT_FOUND);
	}
}

void	ft_heredoc_n_perror(char *input_err, t_mini *env, char c, char d)
{
	ft_heredoc_lexer(input_err, env);
	if (!g_sig && d == 0)
		ft_perror("syntax error near unexpected token `%c\'", c);
	else if (!g_sig)
		ft_perror("syntax error near unexpected token `%c%c\'", c, d);
}

int	ft_write_heredoc_fake(t_redir *redir)
{
	char	*line;
	int		clean_end;

	ft_handle_signals_heredoc(CHILD);
	clean_end = 0;
	while (1 && g_sig == 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file) == 0)
		{
			(free(line), clean_end = 1);
			break ;
		}
		free(line);
	}
	if (!clean_end && g_sig == 0)
		ft_perror("warning: here-document delimited by end-of-file " \
			"(wanted `%s')", redir->file);
	return (EXIT_SUCCESS);
}

void	ft_open_fake_heredoc(t_redir *res, t_mini *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	ft_handle_signals_heredoc(PARENT);
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		status = ft_write_heredoc_fake(res);
		ft_lstclear_env(&env);
		ft_lstclear_redir(&res);
		if (status)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	if (g_sig == SIGINT)
		kill(pid, SIGINT);
}

int	ft_heredoc_lexer(char *input, t_mini *env)
{
	t_token	*res;
	t_redir	*redir;
	t_list	*split;

	res = NULL;
	if (!input)
		return (EXIT_SUCCESS);
	split = ft_split_cmd(&input, 0, 0, 0);
	if (!split)
		return (free(input), EXIT_SUCCESS);
	ft_lstadd_back_token(&res,
		ft_build_token(split, NULL, NULL, ft_strdup("")));
	(ft_lstclear(&split), free(input));
	if (!res)
		return (EXIT_SUCCESS);
	redir = res->redir;
	while (redir && !g_sig && redir->type == HERE_DOC)
		(ft_open_fake_heredoc(redir, env), redir = redir->next);
	ft_lstclear_token(&res);
	return (EXIT_SUCCESS);
}
