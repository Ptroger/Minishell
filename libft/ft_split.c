/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:05:25 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/05 16:45:58 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_memset(str, 0, size + 1);
	return (str);
}

static	size_t	ft_nb_wds(const char *s, size_t i, char c)
{
	size_t	nb_wds;

	if (!s)
		return (0);
	nb_wds = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb_wds += 1;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_wds);
}

static	size_t	ft_nb_char(const char *s, size_t i, char c)
{
	size_t	nb_char;

	nb_char = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (nb_char);
	while (s[i] && s[i] != c)
	{
		nb_char += 1;
		i++;
	}
	return (nb_char);
}

static	void	ft_fill_in_tab(const char *s, size_t *i, size_t nb_char,
		char **tab)
{
	size_t	j;
	size_t	wd;

	wd = 0;
	while (tab[wd][0])
		wd++;
	j = 0;
	while (j < nb_char)
	{
		tab[wd][j] = s[*i];
		*i += 1;
		j++;
	}
	tab[wd][j] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	size_t		i;
	size_t		wd;
	size_t		nb_char;
	size_t		nb_wds;

	i = 0;
	nb_wds = ft_nb_wds(s, i, c);
	tab = (char **)malloc(sizeof(char *) * (nb_wds + 1));
	if (!tab)
		return (NULL);
	wd = 0;
	while (wd < nb_wds)
	{
		while (s[i] && (s[i] == c))
			i++;
		if (!s[i])
			return (tab);
		nb_char = ft_nb_char(s, i, c);
		tab[wd] = ft_strnew(nb_char);
		ft_fill_in_tab(s, &i, nb_char, tab);
		wd += 1;
	}
	tab[wd] = NULL;
	return (tab);
}
