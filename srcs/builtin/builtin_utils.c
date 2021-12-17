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

	if (pile_a)
		temp = *pile_a;
	else
		temp = NULL;
	if (temp)
	{
		max = temp->data;
		while (temp && temp->next)
		{
			temp = temp->next;
			if (ft_strcmp(max, temp->data) < 0)
				max = temp->data;
		}
		return (max);
	}
	return (NULL);
}

t_sort	*ft_add_elem(char *env)
{
	t_sort	*new_elem;

	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return (NULL);
	new_elem->data = ft_strdup(env);
	new_elem->info = NULL;
	new_elem->name = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

int	ft_pile_in_order(t_sort **pile_a)
{
	char	*tmp;
	t_sort	*temp;

	temp = *pile_a;
	if (temp)	
		tmp = temp->data;
	while (temp && temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(tmp, temp->data) > 0)
			return (0);
		tmp = temp->data;
	}
	return (1);
}

int	is_absolute(char *token)
{
	if (token && (token[0] == '.' || token[0] == '/'))
		return (TRUE);
	return (FALSE);
}

char	*find_path(char *token, char **tab)
{
	char *path;
	int i;

	i = 0;
	while (tab[i])
	{
		path = malloc(sizeof(char) * ft_strlen(token) + ft_strlen(tab[i]) + 2);
		if (!path)
			return (NULL);
		path = ft_strcpy(path, tab[i]);
		path = ft_strcat(path, "/");
		path = ft_strcat(path, token);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (ft_strdup(token));
}

void	ft_find_cmd(t_vars *vars, char *token, char **cmd, char **tab)
{
	if (!tab)
	{
		ft_putstr_fd("Error : path could not be found\n", 2);
		return;
	}
	if (is_absolute(token) == TRUE)
	{
		cmd[0] = ft_strdup(token);
		execve(cmd[0], cmd, NULL);
	}
	else
	{
		cmd[0] = find_path(token, tab);
		g_g.ret += execve(cmd[0], cmd, NULL);
		if (cmd[0])
			free(cmd[0]);
		ft_putstr_fd(token, 2);
		throw_error(": command not found", errno);
		clean_exit(vars, errno);
	}
}
