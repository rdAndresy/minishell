/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelamea <bdelamea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:11:15 by bdelamea          #+#    #+#             */
/*   Updated: 2024/05/20 19:52:56 by bdelamea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	my_env(char **cmd, t_mini *env)
{
	t_env	*tmp;

	tmp = env->env;
	if (cmd || !cmd || env || !env)
	{
		while (tmp)
		{
			if (tmp->value)
				ft_fprintf(STDOUT_FILENO, "%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	return (EXIT_SUCCESS);
}
