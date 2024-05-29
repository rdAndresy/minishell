/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelamea <bdelamea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by bdelamea          #+#    #+#             */
/*   Updated: 2024/05/20 19:25:16 by bdelamea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_frees(int count, ...)
{
	va_list		args;
	int			i;
	char		*str;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		str = va_arg(args, char *);
		free(str);
		i++;
	}
	va_end(args);
}
