/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:26:44 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:26:45 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_back(t_sort **sort, t_sort *new)
{
	t_sort	*lst;

	if (!sort)
		return ;
	if (!*sort)
	{
		*sort = new;
		return ;
	}
	lst = *sort;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new;
}

void	set_envs(t_vars *vars)
{
	t_sort	*envs;
	int		temp;

	envs = vars->t_env;
	while (envs && envs->next)
	{
		vars->tab_size++;
		envs = envs->next;
	}
	if (vars->real_envs)
		destroy_tab(vars->real_envs);
	temp = vars->tab_size;
	vars->real_envs = malloc(sizeof(char *) * (temp + 2));
	envs = vars->t_env;
	vars->tab_size = 0;
	while (envs && envs->next && vars->tab_size <= temp)
	{
		vars->real_envs[vars->tab_size] = ft_strdup(envs->data);
		vars->tab_size++;
		envs = envs->next;
	}
	vars->real_envs[vars->tab_size] = ft_strdup(envs->data);
	vars->tab_size++;
	vars->real_envs[vars->tab_size] = NULL;
}
