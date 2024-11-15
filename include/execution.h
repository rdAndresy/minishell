#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		execution(t_token *cmds, t_mini *env);
void	ft_clear_redirs(t_token *cmd, t_exec *exec);
int		ft_check_shell_level(t_mini *env);
void	ft_exit_child(t_exec *exec, int status);
int		ft_fd_in(t_exec *exec, int fd[2], int fdp[2]);
int		ft_fd_out(t_exec *exec, int fd[2], int fdp[2]);
int		ft_has_error(t_token *cmd);
void	ft_lstclear_exec(t_exec **exec);
t_exec	*ft_lstnew_exec(t_token *cmds, t_mini *env);
char	**ft_to_table(t_env *env);

#endif