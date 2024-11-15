#include "lexer.h"

int	ft_write_heredoc(t_redir *redir, t_mini *env, int clean_end)
{
	char	*line;

	ft_handle_signals_heredoc(CHILD);
	while (1 && g_sig == 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			clean_end = 1;
			break ;
		}
		if (ft_expand(&line, env, HERE_DOC, 0))
			return (EXIT_FAILURE);
		ft_fprintf(redir->fd, "%s\n", line);
		free(line);
	}
	if (!clean_end && g_sig == 0)
		ft_perror("warning: here-document delimited by end-of-file " \
			"(wanted `%s')", redir->file);
	return (EXIT_SUCCESS);
}

// Displays the prompt for heredocs and appends the input in the file
int	ft_create_infile(t_token *cmds, t_redir *redir, t_mini *env, char *name)
{
	pid_t	pid;
	int		status;

	pid = fork();
	ft_handle_signals_heredoc(PARENT);
	if (pid == -1)
		return (free(name), EXIT_FAILURE);
	if (pid == 0)
	{
		redir->fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		if (redir->fd == -1)
			exit(EXIT_FAILURE);
		status = ft_write_heredoc(redir, env, 0);
		(ft_closes(3, env->fd_stdin, env->fd_stdout, redir->fd),
			ft_lstclear_env(&env), ft_lstclear_token(&cmds), free(name));
		if (status)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	if (g_sig == SIGINT)
		kill(pid, SIGINT);
	return (free(redir->file), redir->file = name, EXIT_SUCCESS);
}

void	ft_open_redirs(t_redir *redir, t_token *tmp)
{
	if (tmp->err_redir)
	{
		redir->fd = -2;
		return ;
	}
	if (redir->type == INFILE && !tmp->err_redir)
		redir->fd = open(redir->file, O_RDONLY, S_IRUSR);
	else if (redir->type == APPEND && !tmp->err_redir)
		redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR);
	else if (redir->type == OUTFILE && !tmp->err_redir)
		redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR);
	if (redir->fd == -1)
		tmp->err_redir = 1;
}

// Parse the redirections and check if the file exists
// Manage the creation of the file for the here_doc with file = limiter
int	ft_parse_redir(t_token *cmds, t_token *tmp, t_redir *redir, t_mini *env)
{
	char	*random;
	char	*name;

	if (!redir->file)
		return (EXIT_FAILURE);
	if (redir->type == HERE_DOC)
	{
		random = ft_random_string();
		if (!random)
			return (EXIT_FAILURE);
		name = ft_strjoin(".tmpfile", random);
		free(random);
		if (!name)
			return (free(name), EXIT_FAILURE);
		if (ft_create_infile(cmds, redir, env, name))
			return (free(name), EXIT_FAILURE);
		redir->fd = open(name, O_RDONLY, S_IRUSR);
	}
	else
		ft_open_redirs(redir, tmp);
	return (EXIT_SUCCESS);
}
