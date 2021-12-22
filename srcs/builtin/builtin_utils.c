/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:02:44 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:29:15 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sort	*ft_add_elem(char *env)
{
	t_sort	*new_elem;

	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return (NULL);
	if (!env)
		new_elem->data = NULL;
	else
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

char	*find_path(t_vars *vars, char *token, char **tab)
{
	char	*path;
	int		i;

	i = 0;
	while (tab[i])
	{
		path = malloc(sizeof(char) * ft_strlen(token) + ft_strlen(tab[i]) + 2);
		if (!path)
			return (NULL);
		path = ft_strcpy(path, tab[i]);
		path = ft_strcat(path, "/");
		path = ft_strcat(path, token);
		if (is_dir(vars, path, 2) == FALSE)
		{
			if (access(path, X_OK) == 0)
				return (path);
		}
		i++;
		free(path);
	}
	return (ft_strdup(token));
}

int	check_path(t_vars *vars, char *path, int is_exec)
{
	if (is_dir(vars, path, TRUE) == FALSE)
	{
		if (access(path, X_OK) == 0)
			return (TRUE);
		else if (is_exec == TRUE)
		{
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			throw_error(NULL, errno);
			clean_exit(vars, 126);
		}
	}
	return (FALSE);
}

void	ft_find_cmd(t_vars *vars, char *token, char ***cmd, char **tab)
{
	set_envs(vars);
	if (!tab)
	{
		ft_putstr_fd("Error : path could not be found\n", 2);
		clean_exit(vars, 1);
	}
	if (*cmd && *cmd[0])
		free(*cmd[0]);
	if (is_absolute(token) == TRUE)
	{
		*cmd[0] = ft_strdup(token);
		if (check_path(vars, *cmd[0], TRUE) == TRUE)
			execve(*cmd[0], *cmd, vars->real_envs);
	}
	else
	{
		if (ft_strcmp(token, "<<") == 0 || ft_strcmp(token, "|") == 0)
			clean_exit(vars, 0);
		else
			*cmd[0] = find_path(vars, token, tab);
		g_g.ret = execve(*cmd[0], *cmd, vars->real_envs);
		ft_putstr_fd(token, 2);
		throw_error(": command not found", 127);
		clean_exit(vars, 127);
	}
}
