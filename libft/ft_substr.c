/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:12:44 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/05 19:30:21 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start > (unsigned int)ft_strlen(s))
		return (ft_calloc(sizeof(char), 1));
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	while (s[i] && i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
