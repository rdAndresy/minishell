/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelamea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by bdelamea          #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by bdelamea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = -1;
	srclen = ft_strlen(src);
	if (srclen + 1 < size)
		while (++i < srclen + 1)
			dst[i] = src[i];
	else if (size > 0)
	{
		while (++i < size - 1)
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (srclen);
}
