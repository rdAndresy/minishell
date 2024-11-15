#include "signals.h"

int	ft_return(int situation)
{
	g_sig = 0;
	if (situation == SIGINT)
		return (EXIT_INT);
	if (situation == SIGQUIT)
		return (EXIT_QUIT);
	return (EXIT_SUCCESS);
}

void	ft_handle_signals_exec(void)
{
	signal(SIGINT, ft_interrupt_exec);
	signal(SIGQUIT, ft_quit_exec);
}

void	ft_handle_signals_builtins(void)
{
	signal(SIGPIPE, SIG_IGN);
}

void	ft_handle_signals_heredoc(int level)
{
	if (level == CHILD)
	{
		signal(SIGINT, ft_interrupt_heredoc_child);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, ft_interrupt_heredoc_parent);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_handle_signals_main(void)
{
	signal(SIGINT, ft_interrupt_main);
	signal(SIGQUIT, SIG_IGN);
}
