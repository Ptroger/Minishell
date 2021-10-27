/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:37:28 by aribesni          #+#    #+#             */
/*   Updated: 2021/09/21 11:10:09 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_l(const char *str, char c)
{
	int		i;

	i = 0;
	while (*str && *str != c)
	{
		str++;
		i++;
	}
	return (i);
}

static int	ft_count_w(const char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		w;

	i = 0;
	w = ft_count_w(str, c);
	tab = (char **)malloc(sizeof(char*) * (w + 1));
	if (!tab)
		return (NULL);
	while (i < w)
	{
		j = 0;
		while (*str && *str == c)
			str++;
		tab[i] = (char *)malloc(sizeof(char) * (ft_count_l(str, c) + 1));
		if (!tab[i])
			return (NULL);
		while (*str && *str != c)
			tab[i][j++] = *str++;
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = (NULL);
	return (tab);
}
