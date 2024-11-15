#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	ft_clear_tmpfiles(void);
void	ft_handle_signals_builtins(void);
void	ft_handle_signals_exec(void);
void	ft_interrupt_heredoc_fake(int catch);
void	ft_handle_signals_heredoc(int level);
void	ft_handle_signals_main(void);
void	ft_interrupt_main(int catch);
void	ft_interrupt_heredoc_child(int catch);
void	ft_interrupt_heredoc_parent(int catch);
void	ft_interrupt_exec(int catch);
void	ft_quit_exec(int catch);
void	ft_quit_heredoc(int catch);
int		ft_rank_env(t_env **env);
int		ft_return(int situation);

#endif