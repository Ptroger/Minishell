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
		ft_putstr_fd_echo(temp->token, STDOUT_FILENO);
		if (temp->next && ft_is_key(temp->next->token) == 0)
			ft_putstr_fd_echo(" ", STDOUT_FILENO);
		temp = temp->next;
	}
	if (ft_is_key(temp->token) == 0)
		ft_putstr_fd_echo(temp->token, STDOUT_FILENO);
	ft_putstr_fd_echo("\n", STDOUT_FILENO);
}

void	ft_echo_n(t_list *tokens)
{
	t_list *temp;

	temp = tokens;
	while (temp->next && ft_is_key(temp->token) == 0)
	{
		ft_putstr_fd_echo(temp->token, STDOUT_FILENO);
		if (temp->next && ft_is_key(temp->next->token) == 0)
			ft_putstr_fd_echo(" ", STDOUT_FILENO);
		temp = temp->next;
	}
	if (ft_is_key(temp->token) == 0)
		ft_putstr_fd_echo(temp->token, STDOUT_FILENO);
}

void	ft_call_echo(t_list *tokens)
{
	if (!tokens->next)
		ft_putstr_fd_echo("\n", STDOUT_FILENO);
	else if (ft_strcmp(tokens->next->token, "-n") == 0)
		ft_echo_n(tokens->next->next);
	else
		ft_echo(tokens->next);
}