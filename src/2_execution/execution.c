#include "execution.h"

void	ft_exec(t_exec *exec)
{
	if (exec->curr->next && !exec->curr->next->next && exec->fd[1] == -1)
		ft_exit_child(exec, EXIT_FAILURE);
	if (exec->curr->is_builtin)
		ft_builtin_exec(exec, IN_CHILD_EXEC);
	ft_free_table(exec->env->table_env);
	exec->env->table_env = ft_to_table(exec->env->env);
	if (!exec->curr->is_builtin)
		execve(exec->curr->cmd, exec->curr->args, exec->env->table_env);
	ft_perror("%s: %s", exec->curr->args[0], strerror(errno));
	ft_exit_child(exec, EXIT_CMD_NOT_FOUND);
}

void	ft_parent_process(t_exec *exec)
{
	ft_handle_signals_exec();
	if (g_sig)
		kill(exec->pid, SIGINT);
	close(exec->fdp[1]);
	if (exec->curr->previous)
		close(exec->fd[0]);
	if (!exec->curr->next)
		close(exec->fdp[0]);
	if (exec->curr->next)
	{
		close(exec->fd[0]);
		exec->fd[0] = exec->fdp[0];
	}
}

void	ft_child_process(t_exec *exec)
{
	int	error;

	ft_handle_signals_exec();
	error = ft_has_error(exec->curr);
	if (error != EXIT_SUCCESS)
		ft_exit_child(exec, error);
	if (ft_fd_in(exec, exec->fd, exec->fdp) == EXIT_FAILURE
		|| ft_fd_out(exec, exec->fd, exec->fdp) == EXIT_FAILURE)
		ft_exit_child(exec, EXIT_FAILURE);
	ft_clear_redirs(exec->cmds, exec);
	ft_exec(exec);
}

int	ft_init_fork(t_exec *exec, int status)
{
	if (exec->curr->next && pipe(exec->fdp) == -1)
		return (ft_perror("pipe: creation failed"), EXIT_FAILURE);
	else if (!exec->curr->next)
	{
		exec->fdp[0] = dup(exec->fd[0]);
		exec->fdp[1] = dup(exec->fd[1]);
	}
	exec->pid = fork();
	if (exec->pid == -1)
		return (ft_perror("fork: creation failed"), EXIT_FAILURE);
	if (exec->pid == 0)
		ft_child_process(exec);
	else
		ft_parent_process(exec);
	exec->curr = exec->curr->next;
	if (!exec->curr)
	{
		(waitpid(exec->pid, &status, 0),
			exec->final_status = WEXITSTATUS(status));
		if (g_sig)
			exec->final_status = ft_return(g_sig);
	}
	return (EXIT_SUCCESS);
}

int	execution(t_token *cmds, t_mini *env)
{
	int			status;
	t_exec		*exec;

	exec = ft_lstnew_exec(cmds, env);
	if (!exec)
		return (ft_lstclear_token(&cmds), EXIT_FAILURE);
	if (!cmds->next && !ft_is_builtin(cmds->cmd))
		status = ft_builtin_exec(exec, OUT_CHILD_EXEC);
	else
	{
		while (exec->curr)
			if (ft_init_fork(exec, 0) != EXIT_SUCCESS)
				break ;
		status = exec->final_status;
		while (wait(NULL) != -1)
			;
	}
	if (g_sig)
	{
		g_sig = 0;
		if (!ft_check_shell_level(env))
			printf("\n");
	}
	return (ft_lstclear_exec(&exec), ft_lstclear_token(&cmds), status);
}
