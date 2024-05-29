/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoit <benoit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by bdelamea          #+#    #+#             */
/*   Updated: 2024/03/24 21:04:49 by benoit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (*alst == NULL)
		*alst = new;
	else
	{
		new->previous = ft_lstlast(*alst);
		ft_lstlast(*alst)->next = new;
	}
}

void	ft_lstadd_back_basic(t_basic **alst, t_basic *new)
{
	if (*alst == NULL)
		*alst = new;
	else
	{
		new->previous = ft_lstlast_basic(*alst);
		ft_lstlast_basic(*alst)->next = new;
	}
}

void	ft_lstadd_back_token(t_token **alst, t_token *new)
{
	if (*alst == NULL)
		*alst = new;
	else
	{
		new->previous = ft_lstlast_token(*alst);
		ft_lstlast_token(*alst)->next = new;
	}
}

void	ft_lstadd_back_redir(t_redir **alst, t_redir *new)
{
	if (*alst == NULL)
		*alst = new;
	else
		ft_lstlast_redir(*alst)->next = new;
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	if (*alst == NULL)
		*alst = new;
	else
		ft_lstlast_env(*alst)->next = new;
}
