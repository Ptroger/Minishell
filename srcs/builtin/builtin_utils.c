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

char	*ft_return_max(t_sort **pile_a)
{
	char	*max;
	t_sort	*temp;

	temp = *pile_a;
	max = temp->data;
	while (temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(max, temp->data) < 0)
			max = temp->data;
	}
	return (max);
}

void	ft_add_elem(t_sort **sort, char *env)
{
	t_sort	*new_elem;

	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return ;
	new_elem->data = ft_strdup(env);
	new_elem->info = ft_strdup("toto");
	new_elem->name = ft_strdup("toto");
	new_elem->next = *sort;
	*sort = new_elem;
}

int	ft_pile_in_order(t_sort **pile_a)
{
	char	*tmp;
	t_sort	*temp;

	temp = *pile_a;
	tmp = temp->data;
	while (temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(tmp, temp->data) > 0)
			return (0);
		tmp = temp->data;
	}
	return (1);
}

char	*find_path(char *token, char *tab)
{
	char	*path;

	path = malloc(sizeof(char) * ft_strlen(token) + ft_strlen(tab) + 2);
	path = ft_strcpy(path, tab);
	path = ft_strcat(path, "/");
	path = ft_strcat(path, token);
	return (path);
}

void	ft_find_cmd(t_vars **vars, char *token, char **cmd, char **tab)
{
	int		i;

	i = 0;
	(void)vars;
	cmd[0] = ft_strdup(token);
	if (execve(cmd[0], cmd, 0) == -1)
	{
		free(cmd[0]);
		if (!tab)
		{
			ft_putstr_fd("Error : path could not be found\n", 2);
			return ;
		}
		while (tab[i])
		{
			cmd[0] = find_path(token, tab[i]);
			g_g.ret = execve(cmd[0], cmd, 0);
			if (g_g.ret == -1)
				i++;
			free(cmd[0]);
		}
	}
}
