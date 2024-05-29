/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelamea <bdelamea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:56:15 by benoit            #+#    #+#             */
/*   Updated: 2024/05/23 19:18:28 by bdelamea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_closes(int count, ...)
{
	va_list	args;
	int		i;
	int		fd;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		fd = va_arg(args, int);
		if (read(fd, NULL, 0) != -1)
			close(fd);
		close(fd);
		i++;
	}
	va_end(args);
}
