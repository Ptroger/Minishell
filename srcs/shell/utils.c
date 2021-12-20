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
