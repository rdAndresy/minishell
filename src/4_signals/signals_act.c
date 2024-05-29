/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_act.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoit <benoit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:31:48 by bdelamea          #+#    #+#             */
/*   Updated: 2024/05/29 15:09:50 by benoit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
