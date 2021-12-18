/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:45:10 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 09:37:22 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_list *tokens)
{
	t_list *temp;

	temp = tokens;
	while (temp->next && ft_is_key(temp->token) == 0)
	{
		ft_putstr_fd(temp->token, STDOUT_FILENO);
		if (temp->next && ft_is_key(temp->next->token) == 0)
			ft_putstr_fd(" ", STDOUT_FILENO);
		temp = temp->next;
	}
	if (ft_is_key(temp->token) == 0)
		ft_putstr_fd(temp->token, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_echo_n(t_list *tokens)
{
	t_list *temp;

	temp = tokens;
	while (temp->next && ft_is_key(temp->token) == 0)
	{
		ft_putstr_fd(temp->token, STDOUT_FILENO);
		if (temp->next && ft_is_key(temp->next->token) == 0)
			ft_putstr_fd(" ", STDOUT_FILENO);
		temp = temp->next;
	}
	if (ft_is_key(temp->token) == 0)
		ft_putstr_fd(temp->token, STDOUT_FILENO);
}

void	ft_call_echo(t_list *tokens)
{
	int		i;

	i = 0;
	if (!tokens->next)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (tokens->next && tokens->next->token && tokens->next->token[0] == '-' && tokens->next->token[1] == 'n')
	{
		while (tokens->next->token[0] == '-' && tokens->next->token[1] == 'n')
		{
			i = 0;
			while (tokens->next->token && tokens->next->token[i] == 'n')
				i++;
			tokens = tokens->next;
		}
		if (tokens->next)
			ft_echo_n(tokens->next);
	}
	else
		ft_echo(tokens->next);
}