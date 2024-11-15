#include "execution.h"

int	ft_find_redir(t_token *cmd, t_type type)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (type == INFILE
			&& (tmp->type == INFILE || tmp->type == HERE_DOC))
			return (EXIT_FAILURE);
		if (type == OUTFILE
			&& (tmp->type == OUTFILE || tmp->type == APPEND))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_collect_fd(t_redir *redir, t_type type)
{
	t_redir	*tmp;
	int		fd;

	if (type == INFILE)
		tmp = ft_lstlast_redir(redir);
	else
		tmp = redir;
	while (tmp)
	{
		if (type == INFILE && (tmp->type == INFILE || tmp->type == HERE_DOC)
			&& tmp->fd != -1)
			return (fd = tmp->fd);
		if (type == OUTFILE && (tmp->type == OUTFILE || tmp->type == APPEND)
			&& tmp->fd != -1)
			fd = tmp->fd;
		if (type == INFILE)
			tmp = tmp->previous;
		else
			tmp = tmp->next;
	}
	return (fd);
}

int	ft_apply_redir(t_token *cmd, t_type type)
{
	int	fd;

	if (type == INFILE)
	{
		fd = ft_collect_fd(ft_lstlast_redir(cmd->redir), INFILE);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (ft_perror("dup2: failed for in-redir"), EXIT_FAILURE);
	}
	else
	{
		fd = ft_collect_fd(cmd->redir, OUTFILE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (ft_perror("dup2: failed for out-redir"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_fd_in(t_exec *exec, int fd[2], int fdp[2])
{
	if (exec->curr->redir && ft_find_redir(exec->curr, INFILE))
	{
		if (ft_apply_redir(exec->curr, INFILE))
			return (EXIT_FAILURE);
	}
	else if (fd[0] != -1)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (ft_perror("dup2: failed for output"), EXIT_FAILURE);
	}
	ft_closes(2, fdp[0], fd[0]);
	return (EXIT_SUCCESS);
}

int	ft_fd_out(t_exec *exec, int fd[2], int fdp[2])
{
	if (exec->curr->redir && ft_find_redir(exec->curr, OUTFILE))
	{
		if (ft_apply_redir(exec->curr, OUTFILE))
			return (EXIT_FAILURE);
	}
	else if (exec->curr->next)
	{
		if (dup2(fdp[1], STDOUT_FILENO) == -1)
			return (ft_perror("dup2: failed for output"), EXIT_FAILURE);
	}
	else
	{
		if (dup2(exec->env->fd_stdout, STDOUT_FILENO) == -1)
			return (ft_perror("dup2: failed for output"), EXIT_FAILURE);
	}
	ft_closes(4, fdp[1], fd[1], exec->env->fd_stdout, exec->env->fd_stdin);
	return (EXIT_SUCCESS);
}
