/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:10:10 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:10:11 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_g;

t_vars	*ft_init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	vars->state = BASIC;
	vars->token_size = TOKENSIZE;
	vars->finish_line = FALSE;
	vars->tab_size = 0;
	vars->exit_status = 0;
	vars->stdin = -1;
	vars->stdout = -1;
	vars->path = NULL;
	vars->real_envs = NULL;
	vars->tokens = NULL;
	vars->t_env = NULL;
	vars->t_exp = NULL;
	vars->store = NULL;
	vars->original = NULL;
	g_g.ret = 0;
	g_g.pid = 0;
	return (vars);
}

void	destroy_env(t_sort **envs)
{
	t_sort	*temp;

	while (*envs)
	{
		temp = *envs;
		if (temp->data)
			free(temp->data);
		if (temp && temp->name)
			free(temp->name);
		if (temp->info)
			free(temp->info);
		*envs = (*envs)->next;
		if (temp)
			free(temp);
	}
	*envs = NULL;
}

void	destroy_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	destroy_store(t_pipe **store)
{
	t_pipe	*temp;

	while (*store)
	{
		temp = *store;
		if (temp->token)
			free(temp->token);
		destroy_tab(temp->cmd);
		destroy_tab(temp->cell);
		*store = (*store)->next;
		if (temp)
			free(temp);
	}
	if (*store)
		free(*store);
	*store = NULL;
}

void	destroy_vars(t_vars *vars)
{
	if (vars)
	{
		ft_lstclear(&vars->tokens, free);
		destroy_env(&vars->t_exp);
		destroy_env(&vars->t_env);
		if (vars->path)
			destroy_tab(vars->path);
		destroy_store(&vars->store);
	}
}
