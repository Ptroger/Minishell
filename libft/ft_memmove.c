/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:53:01 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/04 13:04:19 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_match(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		if (src + i == dst)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (dst);
	if (src < dst)
	{
		if (get_match((char *)dst, (char *)src, len) == 1)
		{
			while ((int)len > 0)
			{
				((char *)dst)[len - 1] = ((char *)src)[len - 1];
				len--;
			}
			return (dst);
		}
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	}
	else
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}
