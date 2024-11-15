#include "signals.h"

void	ft_interrupt_exec(int catch)
{
	g_sig = catch;
}

void	ft_quit_exec(int catch)
{
	ft_interrupt_exec(catch);
	ft_fprintf(2, "Quit: (core dumped)\n");
}

void	ft_interrupt_main(int catch)
{
	g_sig = catch;
	close(STDIN_FILENO);
}

void	ft_interrupt_heredoc_child(int catch)
{
	g_sig = catch;
	printf("\n");
	close(STDIN_FILENO);
}

void	ft_interrupt_heredoc_parent(int catch)
{
	g_sig = catch;
}
