#include "execution.h"

void	ft_clear_redirs(t_token *cmd, t_exec *exec)
{
	t_token	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir)
			ft_lstclear_redir(&tmp->redir);
		tmp = tmp->next;
	}
	if (exec->fd[0] > 1 && ioctl(exec->fd[0], FIOCLEX) != -1)
		close(exec->fd[0]);
	if (exec->fd[1] > 1 && ioctl(exec->fd[1], FIOCLEX) != -1)
		close(exec->fd[1]);
	if (exec->fdp[0] > 1 && ioctl(exec->fdp[0], FIOCLEX) != -1)
		close(exec->fd[0]);
	if (exec->fdp[1] > 1 && ioctl(exec->fdp[1], FIOCLEX) != -1)
		close(exec->fd[0]);
}

void	ft_lstclear_exec(t_exec **exec)
{
	if ((*exec)->fd[0] > 1 && ioctl((*exec)->fd[0], FIOCLEX) != -1)
		close((*exec)->fd[0]);
	if ((*exec)->fd[1] > 1 && ioctl((*exec)->fd[1], FIOCLEX) != -1)
		close((*exec)->fd[1]);
	if ((*exec)->fdp[0] > 1 && ioctl((*exec)->fdp[0], FIOCLEX) != -1)
		close((*exec)->fdp[0]);
	if ((*exec)->fdp[1] > 1 && ioctl((*exec)->fdp[1], FIOCLEX) != -1)
		close((*exec)->fdp[1]);
	free((*exec));
	exec = NULL;
}

t_exec	*ft_lstnew_exec(t_token *cmds, t_mini *env)
{
	t_exec	*exec;

	if (!cmds || !env)
		return (NULL);
	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (ft_perror("malloc failed"), NULL);
	exec->cmds = cmds;
	exec->curr = cmds;
	exec->env = env;
	exec->pid = 0;
	exec->final_status = -1;
	exec->fdp[0] = -1;
	exec->fdp[1] = -1;
	exec->fd[0] = dup(env->fd_stdin);
	exec->fd[1] = dup(env->fd_stdout);
	if (exec->fd[0] == -1 || exec->fd[1] == -1)
		(ft_perror("dup2 failed"), free(exec));
	return (exec);
}

void	ft_exit_child(t_exec *exec, int status)
{
	if (status == EXIT_NO_CMD)
		status = EXIT_SUCCESS;
	ft_lstclear_token(&exec->cmds);
	ft_lstclear_env(&exec->env);
	ft_lstclear_exec(&exec);
	exit(status);
}

int	ft_has_error(t_token *cmd)
{
	if (!cmd->cmd || cmd->err_redir)
		return (EXIT_FAILURE);
	if (!ft_strncmp(cmd->cmd, ERROR_NOT_A_DIR, ft_strlen(cmd->cmd)))
		return (EXIT_NOT_A_DIR);
	if (!ft_strncmp(cmd->cmd, ERROR_NO_CMD, ft_strlen(cmd->cmd)))
		return (EXIT_NO_CMD);
	if (!ft_strncmp(cmd->cmd, ERROR_EMPTY_CMD, ft_strlen(cmd->cmd)))
		return (EXIT_EMPTY_CMD);
	if (!ft_strncmp(cmd->cmd, ERROR_NO_SUCH_FOD, ft_strlen(cmd->cmd)))
		return (EXIT_NO_SUCH_FOD);
	if (!ft_strncmp(cmd->cmd, ERROR_DIR_NOT_FOUND, ft_strlen(cmd->cmd)))
		return (EXIT_DIR_NOT_FOUND);
	if (!ft_strncmp(cmd->cmd, ERROR_CMD_NOT_FOUND, ft_strlen(cmd->cmd))
		|| !ft_strncmp(cmd->cmd, ERROR_NO_ENV, ft_strlen(cmd->cmd)))
		return (EXIT_CMD_NOT_FOUND);
	return (EXIT_SUCCESS);
}
