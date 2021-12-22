/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:15:11 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:15:13 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	vars->tokens = ft_lstnew((void *)token, 0);
}

void	ft_putstr_lst(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		write(1, &token[i], 1);
		i++;
	}
}

t_sort	*init_temp(void)
{
	t_sort	*temp_exp_2;

	temp_exp_2 = malloc(sizeof(t_sort));
	if (!temp_exp_2)
		return (NULL);
	temp_exp_2->data = NULL;
	temp_exp_2->info = NULL;
	temp_exp_2->name = NULL;
	return (temp_exp_2);
}

void	ft_destroy_tmp(t_sort *temp_env_2, t_sort *temp_exp_2)
{
	if (temp_exp_2)
		destroy_tmp_env(temp_exp_2);
	if (temp_env_2)
		destroy_tmp_env(temp_env_2);
}
