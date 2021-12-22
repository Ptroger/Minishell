/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:32:27 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/22 10:32:29 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[j] == ' ')
			j++;
		i++;
	}
	if (j == i)
		return (FALSE);
	return (TRUE);
}

int	check_pipe(char *str)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			j = i;
		i++;
	}
	i = j + 1;
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	if (!str[i] && j != -1)
	{
		ft_putstr_fd("Pipe at the end of the line\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

void	cpy_env(t_sort *temp, char **env, int i, int *j)
{
	while (env[i][*j] != '=')
	{
		temp->name[*j] = env[i][*j];
		*j += 1;
	}
}

int	check_quote(char *str)
{
	int		i;
	int		count;
	char	type;

	type = 0;
	count = 0;
	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i])
		type = str[i];
	i = 0;
	while (str[i])
	{
		if (str[i] == type)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (TRUE);
	ft_putstr_fd("No matching quotes found\n", 2);
	return (FALSE);
}

int	find_path_2(char *token, char **tab)
{
	char	*path;
	int		i;

	i = 0;
	while (tab[i])
	{
		path = malloc(sizeof(char) * ft_strlen(token) + ft_strlen(tab[i]) + 2);
		if (!path)
			return (FALSE);
		path = ft_strcpy(path, tab[i]);
		path = ft_strcat(path, "/");
		path = ft_strcat(path, token);
		if (access(path, X_OK) == 0)
		{
			free(path);
			return (TRUE);
		}
		i++;
		free(path);
	}
	return (FALSE);
}
