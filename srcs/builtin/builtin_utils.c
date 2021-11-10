/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:02:44 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/09 17:02:45 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *token, char *tab)
{
	char	*path;

	path = malloc(sizeof(char) * ft_strlen(token) + ft_strlen(tab) + 2);
	path = ft_strcpy_ari(path, tab);
	path = ft_strcat(path, "/");
	path = ft_strcat(path, token);
	return (path);
}

void	ft_find_cmd(char *token, char **cmd, char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		cmd[0] = find_path(token, tab[i]);
		if (execve(cmd[0], cmd, 0) == -1)
			i++;
		free(cmd[0]);
	}
}
