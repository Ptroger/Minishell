/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:30:50 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/06 16:05:15 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int	ft_charcmp(char c, const char *d)
{
	int	i;

	i = 0;
	while (d[i])
	{
		if (d[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[i] && ft_charcmp(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1) - 1;
	if (i == j + 1)
		return (ft_strdup(""));
	while (s1[j] && j >= 0 && ft_charcmp(s1[j], set) == 1)
		j--;
	return (ft_substr(s1, (size_t)i, (size_t)(j - i + 1)));
}
