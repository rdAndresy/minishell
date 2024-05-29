/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoit <benoit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:14:41 by benoit            #+#    #+#             */
/*   Updated: 2024/05/29 15:16:24 by benoit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_check_shell_level(t_mini *env)
{
	t_env	*tmp;

	tmp = env->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
		{
			if (ft_atoi(tmp->value) > 2)
				return (EXIT_FAILURE);
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
