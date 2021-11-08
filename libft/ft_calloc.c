/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:03:59 by ptroger           #+#    #+#             */
/*   Updated: 2019/12/24 13:55:10 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*res;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	res = (unsigned char *)malloc(size * count);
	if (!res)
		return (NULL);
	ft_bzero(res, count * size);
	return ((void *)res);
}
